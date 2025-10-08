#include <iostream>
#include <string>
#include <vector>

int main() {
    // the list to search
    const std::vector<std::string> names{
        "Jake", "Zac", "Ian", "Ron", "Sam", "Dave"
    };

    // get search term from user (or default to "Sam")
    std::cout << "Enter name to search (press Enter to search \"Sam\"): ";
    std::string query;
    std::getline(std::cin, query);
    if (query.empty()) 
        query = "Sam";

    // perform a simple loop search
    int foundIndex = -1;
    for (std::size_t i = 0; i < names.size(); ++i) {
        if (names[i] == query) {
            foundIndex = static_cast<int>(i);
            break;
        }
    }

    // report result to user
    if (foundIndex >= 0) {
        std::cout << query << " was found at index " << foundIndex << ".\n";
    } else {
        std::cout << query << " was not found in the index.\n";
    }

    return 0;
}
