#include <iostream>
#include <string>
#include <sstream>

int main() {
    // read full name (enter first and last name with space allowed in between)
    std::cout << "Enter your full name: ";
    std::string name;
    std::getline(std::cin, name);

    // read hometown
    std::cout << "Enter your hometown: ";
    std::string hometown;
    std::getline(std::cin, hometown);

    // read and validate age
    int age = 0;
    std::string line;
    while (true) {
        std::cout << "Enter your age: ";
        if (!std::getline(std::cin, line)) return 0; // handle EOF
        std::stringstream ss(line);
        if (ss >> age) {
            char extra;
            if (!(ss >> extra)) break; // valid integer only
        }
        std::cout << "Please enter a whole number for age.\n";
    }

    // output all details with a single cout, each on its own line
    std::cout << "\nYour details:\n" << name << '\n' << hometown << '\n' << age << std::endl;

    return 0;
}
