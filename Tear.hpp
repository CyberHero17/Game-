#pragma once
#include <iostream>
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <list>
#include "Zombie.hpp"

using std::list;
using std::cin;
using std::cout;
using std::endl;


class Zombie;

class Tear
{
public:
    float damage;
    float range;
    float max_speed;
    Vector2D velocity;
    Vector2D coord;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock time;
public:

    Tear(Vector2D coord, sf::Event event);
    Tear();
    int turn(list<Zombie> &Zombies);
    Vector2D getCoord();
    sf::Sprite getSprite();
}; 
std::ostream& operator<<(std::ostream& os, const Tear& t);