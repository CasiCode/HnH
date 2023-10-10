// Basic tests for dice.hpp. Generates 300.000 values and catches any inexpected results

#include <iostream>
#include <stdexcept>
#include <string>
#include <set>

#include "dice.hpp"

int main() {
    int temp;
    std::set<int> allowed;
    std::set<int> appeared;

    Dice dice;
    allowed = {1, 2, 3, 4, 5, 6};
    for (unsigned int i = 0; i < 100000; i++) {
        temp = dice.roll();
        if(allowed.find(temp) == allowed.end()) {
            std::cout << temp;
            std::runtime_error(
                "generated value: " +
                std::to_string(temp) +
                ". Iteration: " +
                std::to_string(i)
            );
        }
        appeared.insert(temp);
    }
    std::cout << "Test #1 passed\n";
    std::cout << "Appeared: ";
    for (int const& it : appeared) {
        std::cout << " " << it;
    }
    std::cout << "\n";
    appeared.clear();

    Dice anotherDice(3);
    allowed = {1, 2, 3};
    for (unsigned int i = 0; i < 100000; i++) {
        temp = anotherDice.roll();
        if(allowed.find(temp) == allowed.end()) {
            std::runtime_error(
                "generated value: " +
                std::to_string(temp) +
                ". Iteration: " +
                std::to_string(i)
            );
        }
        appeared.insert(temp);
    }
    std::cout << "Test #2 passed\n";
    std::cout << "Appeared: ";
    for (int const& it : appeared) {
        std::cout << " " << it;
    }
    std::cout << "\n";
    appeared.clear();

    Dice yetAnotherDice(12);
    allowed = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for (unsigned int i = 0; i < 100000; i++) {
        temp = yetAnotherDice.roll();
        if(allowed.find(temp) == allowed.end()) {
            std::runtime_error(
                "generated value: " +
                std::to_string(temp) +
                ". Iteration: " +
                std::to_string(i)
            );
        }
        appeared.insert(temp);
    }
    std::cout << "Test #3 passed\n";
    std::cout << "Appeared: ";
    for (int const& it : appeared) {
        std::cout << " " << it;
    }
    std::cout << "\n";
    appeared.clear();

    Dice yetAnotherAnotherDice(1);
    allowed = {1};
    for (unsigned int i = 0; i < 100000; i++) {
        temp = yetAnotherAnotherDice.roll();
        if(allowed.find(temp) == allowed.end()) {
            std::runtime_error(
                "generated value: " +
                std::to_string(temp) +
                ". Iteration: " +
                std::to_string(i)
            );
        }
        appeared.insert(temp);
    }
    std::cout << "Test #4 passed\n";
    std::cout << "Appeared: ";
    for (int const& it : appeared) {
        std::cout << " " << it;
    }
    std::cout << "\n";
    appeared.clear();
}