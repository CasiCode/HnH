#pragma once

#include <string>
#include <stdexcept>

#include "creature.hpp"
#include "integer-range.hpp"


class Monster: public Creature {
    public:
        Monster(std::string name,
            int maxHealth,
            int health,
            int attack,
            int defence,
            IntegerRange damage);
};