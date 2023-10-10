#include "../include/creature.hpp"
#include "../include/player.hpp"
#include "../include/integer-range.hpp"


Player::Player(
            std::string name = "playername",
            int maxHealth = 10,
            int health = 10,
            int attack = 10,
            int defence = 4,
            IntegerRange damage = IntegerRange(3, 6),
            int potions = 4)
            : Creature(
                name, maxHealth, health, attack, defence, damage
            ) {
            this->setHealthPotionsAmount(potions);
        }

// returns true if m_healthPotionsAmount > 0
bool Player::canHeal() {
    return this->healthPotionsAmount();
}

void Player::heal() {
    if (this->m_healthPotionsAmount <= 0) {
        throw std::runtime_error("cannot heal with m_healthPotionsAmount equal to 0");
    }
    this->setHealthPoints(this->healthPoints() + this->maxHealthPoints() * HEALTH_POTION_MULTIPLIER);
    this->setHealthPotionsAmount(this->healthPotionsAmount() - 1);

    std::string msg = "[GAME MESSAGE] " + this->name() + " used a health potion";
    this->sendMessage(msg);
}

//getters
int Player::healthPotionsAmount() { return this->m_healthPotionsAmount; }

//setters
void Player::setHealthPotionsAmount(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("cannot set health potions amount to negative value");
    }
    this->m_healthPotionsAmount = std::move(amount);
}