#pragma once

#include <iostream>
#include "Player.hpp"
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

using std::cin;
using std::cout;
using std::endl;
class Player;

class Zombie: public Entity
{
public:

    Zombie(int hp, float speed, sf::Texture texture);
    Zombie();
    void MoveWithoutIntertion(Player& pl);
    int turn(Player& pl);
    void death();

    ~Zombie() {};
};