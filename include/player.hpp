#pragma once

#include <stdexcept>

#include "creature.hpp"
#include "integer-range.hpp"


class Player: public Creature {
    protected:
        const double HEALTH_POTION_MULTIPLIER = 0.3;
        
        int m_healthPotionsAmount;

    public:
        Player() = delete;
        
        Player(
            std::string name,
            int maxHealth,
            int health,
            int attack,
            int defence,
            IntegerRange damage,
            int potions);

        bool canHeal();

        void heal();

        //getters
        int healthPotionsAmount();

        //setters
        void setHealthPotionsAmount(int amount);
};