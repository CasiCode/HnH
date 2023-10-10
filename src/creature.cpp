#include "../include/integer-range.hpp"
#include "../include/dice.hpp"
#include "../include/creature.hpp"
#include "../include/fight.hpp"


Creature::Creature(
    std::string name = "generic creature",
    int maxHealth = 1,
    int health = 1,
    int attack = 1,
    int defence = 1,
    IntegerRange damage = IntegerRange(0, 0)
    ) {
    // unique id is tied to an onject on initializaion and cannot be set manually
    this->m_id = reinterpret_cast<intptr_t>(this);
    this->setName(name);
    this->setMaxHealthPoints(maxHealth);
    this->setHealthPoints(health);
    this->setAttackPoints(attack);
    this->setDefencePoints(defence);
    this->setDamageRange(damage);
}

void Creature::onDeath() {
    this->m_isDead = true;
    std::string msg = "[GAME MESSAGE] " + this->name() + " is now dead.";
    this->sendMessage(msg);
    //this->~Creature(); // DO NOT USE DESTRUCTORS
}

void Creature::registerFight(Fight* fight) {
    this->m_isRegistered = true;
    this->m_fight = fight;
}

void Creature::sendMessage(std::string message) {
    if (!this->m_isRegistered) {
        throw std::logic_error("cannot send message if not registered");
    }
    this->m_fight->registerMessage(message);
}

void Creature::attack(Creature& target) {
    std::string msg = "[GAME MESSAGE] " + this->name() + " attacked " + target.name();
    this->sendMessage(msg);

    int attackModifier = this->attackPoints() - target.defencePoints() + 1;
    Dice dice(ATTACK_DICE_SIDES);
    bool successful = false;
    do {
        int roll = dice.roll();
        if ((roll == 5) or (roll == 6)) {
            successful = true;
            break;
        }
        attackModifier--;
    }
    while (attackModifier > 0);
    if (!successful) {
        this->sendMessage("[GAME MESSAGE] The attack was not successful.");
    }
    if (successful) {
        target.getDamage(this->m_damageRange.getRandomElement());
    }
}

void Creature::getDamage(int damage) {
    std::string msg = "[GAME MESSAGE] " + this->name() + " got " + std::to_string(damage) + " points of damage";
    this->sendMessage(msg);

    if (damage < 0) {
        throw std::invalid_argument("cannot damage creature with less than 0 points of damage");
    }
    this->setHealthPoints(this->healthPoints() - damage);
}

//getters // deleted const keyword
int Creature::id() const { return this->m_id; }
int Creature::maxHealthPoints() const { return this->m_maxHealthPoints; }
int Creature::healthPoints() { return this->m_healthPoints; }
int Creature::attackPoints() { return this->m_attackPoints; }
int Creature::defencePoints() { return this->m_defencePoints; }
bool Creature::isDead() { return this->m_isDead; }
//ref-qualified getters for dynamic member variables
const std::string &Creature::name() & { return this->m_name; }
std::string Creature::name() && { return std::move(this->m_name); }
const IntegerRange &Creature::damageRange() & { return this->m_damageRange; }
IntegerRange Creature::damageRange() && { return std::move(this->m_damageRange); }

//setters
void Creature::setName(std::string name) { this->m_name = std::move(name); }
void Creature::setMaxHealthPoints(int hp) {
    if (hp <= 0) { hp = 0; }
    this->m_maxHealthPoints = std::move(hp);
    if (this->healthPoints() > this->maxHealthPoints()) {
        this->setHealthPoints(this->maxHealthPoints());
    }
}
void Creature::setHealthPoints(int hp) {
    if (hp <= 0) {
        this->onDeath();
        return;
    }
    this->m_healthPoints = std::move(hp);
}
void Creature::setAttackPoints(int ap) {
    if ((ap < ATTACK_POINTS_MIN) or (ap > ATTACK_POINTS_MAX)) {
        throw std::invalid_argument(
            "cannot set creatures attack points to number less than " +
            std::to_string(ATTACK_POINTS_MIN) +
            " or greater than " +
            std::to_string(ATTACK_POINTS_MAX)
        );
    }
    this->m_attackPoints = std::move(ap);
}
void Creature::setDefencePoints(int dp) {
    if ((dp < DEFENCE_POINTS_MIN) or (dp > DEFENCE_POINTS_MAX)) {
        throw std::invalid_argument(
            "cannot set creatures defence points to number less than " +
            std::to_string(DEFENCE_POINTS_MIN) +
            " or greater than " +
            std::to_string(DEFENCE_POINTS_MAX)
        );
    }
    this->m_defencePoints = std::move(dp);
    }
void Creature::setDamageRange(IntegerRange dr) {
    this->m_damageRange.setValues(dr.lowValue(), dr.highValue());
}