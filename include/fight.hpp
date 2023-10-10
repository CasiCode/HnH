#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "player.hpp"
#include "monster.hpp"
#include "dice.hpp"


class Fight {
    protected:
        std::vector<std::string> m_messages;
        std::unordered_map<unsigned int, Player> m_players;
        std::vector<unsigned int> m_playerIDs;
        std::unordered_map<unsigned int, Monster> m_monsters;
        std::vector<unsigned int> m_monsterIDs;

        void makePlayerMoves();

        void makeMonsterMoves();

        void displayRegisteredMessages();

        void onStart();

        bool isRegistered(Player& player);
        bool isRegistered(Monster& monster);

        Player& getPlayerByID(unsigned int id);
        Monster& getMonsterByID(unsigned int id);
    
    public:
        Fight(std::vector<Player> players, std::vector<Monster> monsters);

        void registerCreature(Player& player);
        void registerCreature(Monster& monster);

        // deregistered creatures should be deleted by garbage collector since they leave scope fully on deregistration
        void deregisterCreature(Player& player);
        void deregisterCreature(Monster& monster);

        void registerMessage(std::string message);
};