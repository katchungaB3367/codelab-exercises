#include <iostream>

int main() {
    // explaining numbering to user
    std::cout << "Enter numbers corresponding to months i.e. 1 for January, 2 for February ... 12 for December\n";

    // prompt for user to enter month number
    std::cout << "Enter number (1–12): ";
    int month{};
    if (!(std::cin >> month)) {
        // non-numeric input
        std::cout << "Invalid input. Please enter a number between 1 and 12.\n";
        return 0;
    }

    // use switch to show days in month
    switch (month) {
        // months with 31 days
        case 1:  // January
        case 3:  // March
        case 5:  // May
        case 7:  // July
        case 8:  // August
        case 10: // October
        case 12: // December
            std::cout << "That month has 31 days.\n";
            break;

        // months with 30 days
        case 4:  // April
        case 6:  // June
        case 9:  // September
        case 11: // November
            std::cout << "That month has 30 days.\n";
            break;

        // February
        case 2:
            std::cout << "February has 28 days (29 in a leap year).\n";
            break;

        // invalid month number
        default:
            std::cout << "That is not a valid month number.\n";
            break;
    }

    return 0;
}
