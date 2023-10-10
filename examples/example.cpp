/*
    This is an example of using Player and Monster classes.
    In this example a few players and a few monsters are passed in Fight class,
    which is an automatic fighting game.
*/

#include <vector>

#include "../include/integer-range.hpp"
#include "../src/creature.cpp"
#include "../src/fight.cpp"
#include "../src/player.cpp"
#include "../src/monster.cpp"

int main() {
    std::vector<Player> players = {
        Player("Steve", 10, 10, 6, 4, IntegerRange(3, 5), 4),
        Player("Alex", 10, 10, 6, 4, IntegerRange(3, 5), 4)
    };
    std::vector<Monster> monsters = {
        Monster("Creeper"),
        Monster("Spider"),
        Monster("Zombie")
    };

    Fight fight(players, monsters);
}