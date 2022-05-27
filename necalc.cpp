#include <cstddef>

#include <iostream>
#include <string>
#include <vector>

#include <arby/Nat.hpp>


using namespace com::saxbophone;

int main() {
    std::cout << "necalc v" << NECALC_VERSION_STRING << std::endl;
    arby::Nat accumulator;
    std::string input;
    do {
        if (not input.empty()) {
            std::vector<std::string> parts;
            std::size_t pos = 0;
            while ((pos = input.find(" ")) != std::string::npos) {
                parts.push_back(input.substr(0, pos));
                input.erase(0, pos + 1);
            }
            for (auto part : parts) {
                std::cout << part << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << "> ";
    } while (std::getline(std::cin, input));
    std::cout << std::endl; // print newline on escape/exit
}
