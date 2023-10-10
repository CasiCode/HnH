#pragma once

#include <stdexcept>
#include <string>

#include "integer-range.hpp"
#include "dice.hpp"

class Fight;

class Creature {
    protected:
        const int ATTACK_DICE_SIDES = 6;
        const int ATTACK_POINTS_MIN = 1;
        const int ATTACK_POINTS_MAX = 30;
        const int DEFENCE_POINTS_MIN = 1;
        const int DEFENCE_POINTS_MAX = 30;

        Fight* m_fight = nullptr;
        bool m_isRegistered;
        unsigned int m_id;
        bool m_isDead = false;
        
        std::string m_name;
        int m_maxHealthPoints;
        int m_healthPoints;
        int m_attackPoints;
        int m_defencePoints;
        IntegerRange m_damageRange;

        virtual void onDeath();

    public:
        Creature(
            std::string,
            int maxHealth,
            int health,
            int attack,
            int defence,
            IntegerRange damage
        );

        virtual ~Creature() = default;

        void registerFight(Fight* fight);

        void sendMessage(std::string message);

        virtual void attack(Creature& target);

        void getDamage(int damage);

        //getters
        int id() const;
        int maxHealthPoints() const;
        int healthPoints();
        int attackPoints();
        int defencePoints();
        bool isDead();
        //ref-qualified getters for dynamic member variables
        const std::string &name() &;
        std::string name() &&;
        const IntegerRange &damageRange() &;
        IntegerRange damageRange() &&;

        //setters
        void setName(std::string name);
        void setMaxHealthPoints(int hp);
        void setHealthPoints(int hp);
        void setAttackPoints(int ap);
        void setDefencePoints(int dp);
        void setDamageRange(IntegerRange dr);
};