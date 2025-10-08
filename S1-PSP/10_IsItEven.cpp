#include <iostream>
#include <string>
#include <sstream>

// return one of the two required strings depending on condition
std::string checkEven(int value) {
    return (value % 2 == 0)
         ? "The provided number is even"
         : "The provided number is odd";
}

int main() {
    // prompt the user to enter the number
    std::cout << "Please enter an integer: ";

    // read a full line and validate whether the number entered is an integer
    std::string line;
    if (!std::getline(std::cin, line)) return 0;

    std::stringstream ss(line);
    int num{};
    char extra{};
    if (!(ss >> num) || (ss >> extra)) {
        std::cerr << "That is not a valid integer." << std::endl;
        return 1;
    }

    // get message from the function and print it from main
    std::cout << checkEven(num) << std::endl;

    return 0;
}
