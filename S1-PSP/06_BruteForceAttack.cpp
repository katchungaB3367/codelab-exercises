#include <iostream>
#include <string>

int main() {
    // correct password (string used to accept set input)
    const std::string correct = "12345";

    // limit to the number of passwords entered
    const int max_tries = 5;
    int used = 0;

    std::string entry;

    // letting the user try until correct or out of attempts
    while (used < max_tries) {
        std::cout << "Enter Password: ";
        if (!std::getline(std::cin, entry)) {
            // handle EOF / input error
            return 0;
        }

        if (entry == correct) {
            std::cout << "Welcome to the Secure Area\n";
            return 0;
        }

        // wrong attempt count
        ++used;
        int remaining = max_tries - used;
        if (remaining > 0) {
            std::cout << "Incorrect. " << remaining
                      << " attempt" << (remaining == 1 ? "" : "s")
                      << " remaining.\n";
        }
    }

    // message to be displayed if the user used up all tries
    std::cout << "Maximum attempts reached. Authorities have been alerted!\n";
    return 0;
}
