#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "../include/player.hpp"
#include "../include/monster.hpp"
#include "../include/dice.hpp"
#include "../include/fight.hpp"

/*
    TO-DO:
    Player damage is not in wanted bounds
*/

void Fight::makePlayerMoves() {
    for (auto& id : this->m_playerIDs) {
        Player& currentPlayer = this->getPlayerByID(id);
        //  currentPlayer either heals if its HP is below 50%
        if ((currentPlayer.healthPoints() <= currentPlayer.maxHealthPoints() * 0.5) and (currentPlayer.canHeal())) {
            currentPlayer.heal();
            continue;
        }
        //  passes its turn if there are no monsters
        if (this->m_monsters.empty()) { continue; }
        //  or attacks a random registered monster:
        //  create a dice with number of sides equal to living monsters number
        Dice dice(this->m_monsterIDs.size());
        /*  roll it to decide which monster from m_monsters will be attacked
            then attack it */
        unsigned int randomMonsterID = this->m_monsterIDs.at(dice.roll() - 1);
        Monster& targetMonster = this->getMonsterByID(randomMonsterID);
        currentPlayer.attack(targetMonster);
        //  if attacked monster is killed deregister it
        if (targetMonster.isDead()) {
            this->deregisterCreature(targetMonster);
        }
    }
}

void Fight::makeMonsterMoves() {
    for (auto& id : this->m_monsterIDs) {
        Monster& currentMonster = this->getMonsterByID(id);
        if (this->m_players.empty()) { continue; }
        Dice dice(this->m_playerIDs.size());
        unsigned int randomPlayerID = this->m_playerIDs.at(dice.roll() - 1);
        Player& targetPlayer = this->getPlayerByID(randomPlayerID);
        currentMonster.attack(targetPlayer);
        if (targetPlayer.isDead()) {
            this->deregisterCreature(targetPlayer);
        }
    }
}

void Fight::displayRegisteredMessages() {
    for (auto& msg : this->m_messages) {
        std::cout << msg + "\n";
    }
    std::cout << "\n";
    this->m_messages.clear();
}

void Fight::onStart() {
    this->displayRegisteredMessages();

    bool fighting = true;
    while(fighting) {
        if (this->m_monsters.empty()) {
            std::cout << "[GAME MESSAGE] The players have won!";
            fighting = false; // breaks the infinite loop if every monster is dead
        }
        if (this->m_players.empty()) {
            std::cout << "[GAME MESSAGE] The monsters have won.";
            fighting = false; // breaks the infinite loop if every player is dead
        }
        makePlayerMoves();
        makeMonsterMoves();
        displayRegisteredMessages();
    }
}

// TO-DO: may cause issues: iterator type is explicitly written
bool Fight::isRegistered(Player& player) {
    std::unordered_map<unsigned int, Player>::const_iterator got = this->m_players.find(player.id());
    if (got == m_players.end()) { return false; }
    return true;
}
bool Fight::isRegistered(Monster& monster) {
    std::unordered_map<unsigned int, Monster>::const_iterator got = this->m_monsters.find(monster.id());
    if (got == m_monsters.end()) { return false; }
    return true;
}

Fight::Fight(std::vector<Player> players = {}, std::vector<Monster> monsters = {}) {
    for (auto& player : players) {
        this->registerCreature(player);
    }
    for (auto& monster : monsters) {
        this->registerCreature(monster);
    }
    this->displayRegisteredMessages();
    onStart();
}

void Fight::registerCreature(Player& player) {
    player.registerFight(this);
    this->m_players.insert({player.id(), std::move(player)});
    this->m_playerIDs.push_back(player.id());

    // debug message creation
    std::string msg = "[SYSTEM MESSAGE] Player " + player.name() + " was registered.";
    this->registerMessage(msg);
}
void Fight::registerCreature(Monster& monster) {
    monster.registerFight(this);
    this->m_monsters.insert({monster.id(), std::move(monster)});
    this->m_monsterIDs.push_back(monster.id());

    // debug message creation
    std::string msg = "[SYSTEM MESSAGE] Monster " + monster.name() + " was registered.";
    this->registerMessage(msg);
}

// deregistered creatures should be deleted by garbage collector since they leave scope fully on deregistration
void Fight::deregisterCreature(Player& player) {
    if (!isRegistered(player)) {
        throw std::invalid_argument("cannot deregister player: it is not registered");
    }
    this->m_players.erase(player.id());
    this->m_playerIDs.erase(std::remove(this->m_playerIDs.begin(), this->m_playerIDs.end(), player.id()), this->m_playerIDs.end());

    // debug message creation
    std::string msg = "[SYSTEM MESSAGE] Player " + player.name() + " was deregistered.";
    this->registerMessage(msg);
}
void Fight::deregisterCreature(Monster& monster) {
    if (!isRegistered(monster)) {
        throw std::invalid_argument("cannot deregister monster: it is not registered");
    }
    this->m_monsters.erase(monster.id());
    this->m_monsterIDs.erase(std::remove(this->m_monsterIDs.begin(), this->m_monsterIDs.end(), monster.id()), this->m_monsterIDs.end());
    
    // debug message creation
    std::string msg = "[SYSTEM MESSAGE] Monster " + monster.name() + " was deregistered.";
    this->registerMessage(msg);
}

Player& Fight::getPlayerByID(unsigned int id) {
    if (std::find(this->m_playerIDs.begin(), this->m_playerIDs.end(), id) == this->m_playerIDs.end()) {
        throw std::invalid_argument("Player id not registered");
    }
    return this->m_players.at(id);
}
Monster& Fight::getMonsterByID(unsigned int id) {
    if (std::find(this->m_monsterIDs.begin(), this->m_monsterIDs.end(), id) == this->m_monsterIDs.end()) {
        throw std::invalid_argument("Monster id not registered");
    }
    return this->m_monsters.at(id);
}

void Fight::registerMessage(std::string message) {
    this->m_messages.push_back(message);
}