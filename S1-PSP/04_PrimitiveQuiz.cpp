#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// make a string lowercase to accept different case inputs
static std::string to_lower(std::string s) {
    for (char &c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

// remove leading/trailing spaces to ensure that extra characters before and after do not cause a mismatch
static std::string trim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch){ return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch){ return !std::isspace(ch); }).base(), s.end());
    return s;
}

int main() {
    // set of countries and capitals
    const std::vector<std::pair<std::string, std::string>> quiz = {
        {"Spain", "Madrid"},
        {"Italy", "Rome"},
        {"France", "Paris"},
        {"Sweden", "Stockholm"},
        {"Switzerland", "Bern"},
        {"Netherlands", "Amsterdam"},
        {"Poland", "Warsaw"},
        {"Czech Republic", "Prague"},
        {"Croatia", "Zagreb"},
        {"Romania", "Bucharest"}
    };

    std::cout << "Capitals quiz — answer the questions below.\n\n";

    for (const auto &q : quiz) {
        const std::string &country = q.first;
        const std::string &capital = q.second;

        std::cout << "What is the capital of " << country << "? ";
        std::string response;
        std::getline(std::cin, response);

        response = to_lower(trim(response));
        std::string correct = to_lower(capital);

        if (response == correct) {
            std::cout << "That is a right answer.\n\n";
        } else {
            std::cout << "Incorrect. The right answer would be " << capital << ".\n\n";
        }
    }

    std::cout << "Quiz finished.\n";
    return 0;
}
