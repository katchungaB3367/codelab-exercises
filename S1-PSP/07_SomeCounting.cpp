#include <iostream>

// Print numbers from start to end using steps
// Works for both positive or negative steps
static void printRange(int start, int end, int step) {
    for (int i = start; (step > 0) ? (i <= end) : (i >= end); i += step) {
        std::cout << i;
        if ((step > 0 && i + step <= end) || (step < 0 && i + step >= end))
            std::cout << ' ';
    }
    std::cout << '\n';
}

int main() {
    // 1) count up 0 to 50 by 1
    std::cout << "1) Count up 0 to 50:\n";
    printRange(0, 50, 1);
    std::cout << '\n';

    // 2) count down 50 to 0 by 1
    std::cout << "2) Count down 50 to 0:\n";
    printRange(50, 0, -1);
    std::cout << '\n';

    // 3) count up 30 to 50 by 1
    std::cout << "3) Count up 30 to 50:\n";
    printRange(30, 50, 1);
    std::cout << '\n';

    // 4) count down 50 to 10 by 2
    std::cout << "4) Count down 50 to 10 by 2s:\n";
    printRange(50, 10, -2);
    std::cout << '\n';

    // 5) count up 100 to 200 by 5
    std::cout << "5) Count up 100 to 200 by 5s:\n";
    printRange(100, 200, 5);
    std::cout << '\n';

    return 0;
}
