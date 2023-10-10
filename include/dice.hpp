#pragma once

#include <random>
//#include <ctime>
#include <stdexcept>

// strongly similar to integerRange. Do we need it?
class Dice {
    protected:
        int m_sides;
        //std::uniform_int_distribution<int> uni;

    public:
        Dice(int sides = 6) {
            this->setSides(sides);
            /*std::random_device rd;
            std::mt19937 rng(rd());
            uni(1, sides);*/
        } 

        int roll() {
            //std::srand(std::time(nullptr)); // use current time as seed for random generator
            return 1 + (rand() % static_cast<int>(this->m_sides));
            //return uni(rng);
        }

        //getters
        int sides() const { return this->m_sides; }

        //setters
        void setSides(int sides) {
            if (sides < 1) {
                throw std::invalid_argument("cannot set dice sides to number lower than 1");
            }
            this->m_sides = std::move(sides);
        }
};