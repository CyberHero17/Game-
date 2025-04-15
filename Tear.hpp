#pragma once
#include <iostream>
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <list>

using std::list;
using std::cin;
using std::cout;
using std::endl;




class Tear
{
public:
    float damage;
    float live_time;
    float max_speed;
    Vector2D velocity;
    Vector2D coord;
    sf::Texture texture;
    sf::Sprite sprite;
public:

    Tear(Vector2D coord, sf::Event event);
    Tear();
    int turn(list<Entity> &Mosters);
    Vector2D getCoord();
    sf::Sprite getSprite();


}; 
