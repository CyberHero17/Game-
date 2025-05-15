#pragma once
#include <iostream>
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <list>
#include "Zombie.hpp"
#include "Player.hpp"

using std::list;
using std::cin;
using std::cout;
using std::endl;


class Zombie;
class Player;
class Tear
{
public:
    sf::Clock animation_time;
    bool Animation;
    float Damage;
    float Range;
    float ShotSpeed;
    float mass;
    Vector2D velocity;
    Vector2D coord;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock time;
public:

    Tear(Player pl, sf::Event event);
    Tear();
    int turn(list<Zombie> &Zombies);
    Vector2D getCoord();
    sf::Sprite getSprite();
    void death();
}; 
std::ostream& operator<<(std::ostream& os, const Tear& t);
