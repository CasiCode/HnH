#include "../include/integer-range.hpp"
#include "../include/creature.hpp"
#include "../include/monster.hpp"


Monster::Monster(
            std::string name = "monstername",
            int maxHealth = 5,
            int health = 5,
            int attack = 5,
            int defence = 3,
            IntegerRange damage = IntegerRange(2, 4))
            : Creature(
                name, maxHealth, health, attack, defence, damage
            ) {}