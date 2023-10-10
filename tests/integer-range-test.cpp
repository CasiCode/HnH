// Basic tests for integer-range.hpp. Generates 300.000 values and catches inexpected behavior

#include <iostream>
#include <stdexcept>
#include <set>

#include "../include/integer-range.hpp"


int main() {
    int temp;
    std::set<int> appeared;
    std::set<int> allowed;

    IntegerRange range(3, 6);
    allowed = {3, 4, 5, 6};
    for (unsigned int i = 0; i < 100000; i++) {
        temp = range.getRandomElement();
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

    IntegerRange anotherRange(5, 12);
    allowed = {5, 6, 7, 8, 9, 10, 11, 12};
    for (unsigned int i = 0; i < 100000; i++) {
        temp = anotherRange.getRandomElement();
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
    std::cout << "Test #2 passed\n";
    std::cout << "Appeared: ";
    for (int const& it : appeared) {
        std::cout << " " << it;
    }
    std::cout << "\n";
    appeared.clear();

    IntegerRange yetAnotherRange(-5, 1);
    allowed = {-5, -4, -3, -2, -1, 0, 1};
    for (unsigned int i = 0; i < 100000; i++) {
        temp = yetAnotherRange.getRandomElement();
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
    std::cout << "Test #3 passed\n";
    std::cout << "Appeared: ";
    for (int const& it : appeared) {
        std::cout << " " << it;
    }
    std::cout << "\n";
    appeared.clear();
}
