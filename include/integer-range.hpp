#pragma once

#include <utility>
#include <cstdlib>


class IntegerRange {
    protected:
        int m_low;
        int m_high;

        void sort() {
            if (!(this->m_low > this->m_high)) { return; }
            int temp = this->m_low;
            this->m_low = this->m_high;
            this->m_high = temp;
        }

    public:
        IntegerRange(int lowValue = 0, int highValue = 0) {
            this->m_low = std::move(lowValue);
            this->m_high = std::move(highValue);
            this->sort();
        }

        virtual ~IntegerRange() = default;

        // returns random number in this Integer Range 
        int getRandomElement() {
            //std::srand(std::time(nullptr)); // use current time as seed for random generator
            //return this->lowValue() + std::rand() % (this->highValue() - this->lowValue() + 1);
            return this->lowValue() + (rand() % static_cast<int>(this->highValue() - this->lowValue() + 1));
        }

        //getters
        int lowValue() { return this->m_low; }
        int highValue() { return this->m_high; }

        // setters
        void setValues(int lowValue, int highValue) {
            this->m_low = std::move(lowValue);
            this->m_high = std::move(highValue);
            if (this->m_low > this->m_high) { this->sort(); }
        }
};