#include <cstddef>

#include <iostream>
#include <string>
#include <vector>

#include <arby/Nat.hpp>
#include <arby/math.hpp>


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
            // tokeniser doesn't handle the last part, so add that if present
            if (not input.empty()) {
                parts.push_back(input);
            }
            // XXX: very basic processing loop for now
            std::cout << "🧮⏳";
            std::cout.flush();
            for (auto it = parts.begin(); it != parts.end(); ++it) {
                // handle operators first then if none match, assume is number
                if (*it == "+") {
                    ++it;
                    accumulator += arby::Nat(*it);
                } else if (*it == "-") {
                    ++it;
                    accumulator -= arby::Nat(*it);
                } else if (*it == "*") {
                    ++it;
                    accumulator *= arby::Nat(*it);
                } else if (*it == "/") {
                    ++it;
                    accumulator /= arby::Nat(*it);
                } else if (*it == "%") {
                    ++it;
                    accumulator %= arby::Nat(*it);
                } else if (*it == "^") {
                    ++it;
                    accumulator = arby::pow(accumulator, arby::Nat(*it));
                } else {
                    accumulator = arby::Nat(*it);
                }
            }
            std::cout << "\33[2K\r"; // erase previously printed line first
            std::cout << "📝⏳";
            std::cout.flush();
            std::string output = (std::string)accumulator;
            std::cout << "\33[2K\r"; // erase previously printed line first
            std::cout << output << std::endl;
        }
        std::cout << "> ";
    } while (std::getline(std::cin, input));
    std::cout << std::endl; // print newline on escape/exit
}
