#include <iostream>
#include <string>

#include <arby/Nat.hpp>


using namespace com::saxbophone;

int main() {
    std::cout << "necalc v" << NECALC_VERSION_STRING << std::endl;
    arby::Nat accumulator;
    std::string input;
    do {
        if (not input.empty()) {
            std::cout << input << std::endl;
        }
        std::cout << "> ";
    } while (std::getline(std::cin, input));
    std::cout << std::endl; // print newline on escape/exit
}
