#pragma once

#include <iostream>
//#include "Structures.cpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

using std::cin;
using std::cout;
using std::endl;

class Player: public Entity
{
public:
    Player(int hp, float speed, sf::Texture texture);
    Player();
    void MoveInertion(sf::Event event);
    void MoveWithoutIntertion(sf::Event event);
    void turn(sf::Event event, bool EnableIntertion);
    void death();
    void getDamage(int D);
    ~Player() {};
};