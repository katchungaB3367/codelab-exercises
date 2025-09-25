// vending_machine.cpp
// Compile with:
//    g++ -std=c++17 vending_machine.cpp -o SmartVendingMachine.exe

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <string>
#include <cctype>
#include <cmath>      // for std::fabs
#include <cstdlib>    // for system("pause")

#ifdef _WIN32
  #include <windows.h>
#endif

using namespace std;

// Represents product slot
class Item {
public:
    Item(const string &c, const string &n,
         const string &cat, double p, int s)
      : code(c), name(n), category(cat),
        price(p), stock(s) {}
    string code, name, category;
    double price;  // in pounds
    int stock;
};

// Encapsulates entire vending workflow
class VendingMachine {
public:
    VendingMachine()
      : credit(0.0), stockFile("stock.txt")
    {
        initDefaultItems();
        loadStock();
    }

    ~VendingMachine() {
        saveStock();
    }

    // Start the interactive loop
    void run() {
        cout << fixed << setprecision(2);

        bool keepGoing = true;
        while (keepGoing) {
            displayMenu();
            cout << "Available credit: £" << credit << "\n";

            Item* product = selectProduct();
            if (!product) break;

            int qty = selectQuantity(product->stock);
            processPurchase(*product, qty);
            keepGoing = promptYesNo(
                "Purchase additional items? Enter (Y) for yes or (N) for no:");
        }

        returnChange();
        cout << "Thank you for your purchase.\n";
    }

private:
    vector<Item> items;
    unordered_map<string,int> lookup;  // code -> index
    double credit;
    const string stockFile;

    // Default catalogue with 4 categories and 4 items in each category, stock = 10
    void initDefaultItems() {
        items = {
            {"A1","Iced Tea 330ml","Beverages",       1.30, 10},
            {"A2","Diet Coke 330ml","Beverages",      1.40, 10},
            {"A3","Water 600ml","Beverages",          1.00, 10},
            {"A4","Cold Coffee","Beverages",          1.95, 10},

            {"B1","Chocolate Biscuit","Sweet Bite",   0.85, 10},
            {"B2","Oaty Bar","Sweet Bite",            1.00, 10},
            {"B3","Brownie","Sweet Bite",             1.10, 10},
            {"B4","Marshmallow Treat","Sweet Bite",   1.00, 10},

            {"C1","Salted Crisps","Snacks",    1.10, 10},
            {"C2","Cheese & Onion Crisps","Snacks",1.15,10},
            {"C3","Spicy Peanuts","Snacks",    1.40, 10},
            {"C4","Pretzels","Snacks",         1.20, 10},

            {"D1","Instant Noodles (Chicken)","Noodles",1.20,10},
            {"D2","Instant Noodles (Beef)","Noodles",  1.25,10},
            {"D3","Cup Noodles (Vegetable)","Noodles", 1.30,10},
            {"D4","Cup Noodles (Seafood)","Noodles",   1.35,10}
        };
        rebuildLookup();
    }

    void rebuildLookup() {
        lookup.clear();
        for (int i = 0; i < (int)items.size(); ++i) {
            lookup[toUpper(items[i].code)] = i;
        }
    }

    void loadStock() {
        ifstream fin(stockFile);
        if (!fin) {
            saveStock();  // create default file
            return;
        }
        string code;
        int stk;
        while (fin >> code >> stk) {
            string up = toUpper(code);
            if (lookup.count(up)) {
                items[lookup[up]].stock = stk;
            }
        }
    }

    void saveStock() {
        ofstream fout(stockFile, ios::trunc);
        for (auto &it : items) {
            fout << it.code << " " << it.stock << "\n";
        }
    }

    void displayMenu() {
        cout << "\n===== MENU =====\n";
        vector<string> cats;
        for (auto &it : items)
            if (find(cats.begin(), cats.end(), it.category) == cats.end())
                cats.push_back(it.category);

        for (auto &cat : cats) {
            cout << "\n-- " << cat << " --\n";
            for (auto &it : items) {
                if (it.category != cat) continue;
                cout << " " << setw(3) << it.code
                     << " | " << setw(22) << it.name
                     << " | £" << setw(4) << it.price;
                if (it.stock <= 0) cout << " | SOLD OUT";
                else             cout << " | stock: " << it.stock;
                cout << "\n";
            }
        }
        cout << "===============\n"
             << "Enter code to buy or Q to exit.\n";
    }
	// Select product function allows users to enter item codes in the vending machine 
    Item* selectProduct() {
        string input;
        while (true) {
            cout << "Insert Code: ";
            if (!(cin >> input)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            string key = toUpper(input);
            if (key == "Q") return nullptr;
            if (!lookup.count(key)) {
                cout << "Invalid code. Try again.\n";
                continue;
            }
            Item &sel = items[lookup[key]];
            if (sel.stock <= 0) {
                cout << sel.name << " is sold out. Pick another.\n";
                continue;
            }
            return &sel;
        }
    }
	
	// Users are able to select the quantity of the item chosen
    int selectQuantity(int maxQty) {
        int qty;
        while (true) {
            cout << "Enter quantity (1 - " << maxQty << "): ";
            if (!(cin >> qty) || qty < 1 || qty > maxQty) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid quantity. Try again.\n";
                continue;
            }
            return qty;
        }
    }
	
	// Purchase is processed with messages to user for credit inputs
    void processPurchase(Item &it, int qty) {
        double total = it.price * qty;
        cout << "You picked: " << qty << " of " << it.name
             << " (£" << total << ")\n";

        if (credit + 1e-9 < total) {
            cout << "Insert £" << (total - credit)
                 << " to proceed.\n";
            acceptPayment(total - credit);
        } else {
            credit -= total;
        }

        cout << "Available credit: £" << credit << "\n";
        dispenseItem(it, qty);
        it.stock -= qty;
        cout << "Remaining credit: £" << credit << "\n";
        suggest(it);
    }
	
	// Accepts the payment (limited to £20 to restrict how much change the machine can return)
    void acceptPayment(double needed) {
        static constexpr double denominations[] =
            {20.00, 10.00, 5.00, 2.00, 1.00,
             0.50, 0.20, 0.10, 0.05};
        double inserted = 0.0;

        cout << "You need £" << needed << ".\n";
        while (inserted + credit + 1e-9 < needed + credit) {
            cout << "Insert coin/bill (you can insert a maximum of £20 bill): ";
            double v = 0;
            if (!(cin >> v)
             || none_of(begin(denominations), end(denominations),
                        [&](double d){ return fabs(d - v) < 1e-6; }))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid denomination. Try again.\n";
                continue;
            }
            inserted += v;
            cout << "Total inserted: £" << inserted << "\n";
        }
        credit += inserted - needed;
    }
	
	// Machine shows dispensing item notification to user for visual feedback
    void dispenseItem(const Item &it, int qty) {
        cout << "\n>> Dispensing " << qty << " of "
             << it.name << " <<\n\n";
    }
	
	// Suggestion allows the machine to ask the user to make another purchase
    void suggest(const Item &it) {
        cout << "Suggestion: ";
        if (it.category == "Beverages")
            cout << "Fancy a snack? Try C1 next time.\n";
        else if (it.category == "Sweet Bite")
            cout << "Pair with a drink: try A1.\n";
        else if (it.category == "Snacks")
            cout << "How about a sweet? Try B1.\n";
        else
            cout << "How about some noodles? Try D1.\n";
    }

    bool promptYesNo(const string &msg) {
        string resp;
        while (true) {
            cout << msg << " ";
            if (!(cin >> resp)) continue;
            char c = tolower(resp[0]);
            if (c == 'y') return true;
            if (c == 'n') return false;
        }
    }

    string toUpper(string s) {
        for (auto &ch : s) ch = toupper((unsigned char)ch);
        return s;
    }

    void returnChange() {
        if (credit > 0.005) {
            cout << "\n>> Returning change: £" << credit << "\n\n";
            credit = 0;
        } else {
            cout << "\nYou have no change due.\n\n";
        }
    }
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "Smart Vending Machine – Version 1\n\n";
    VendingMachine machine;
    machine.run();

#ifdef _WIN32
    // pause so user can see final messages
    system("pause");
#endif

    return 0;
}
