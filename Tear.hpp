#pragma once
#include <iostream>
#include "Structures.cpp"
#include <SFML/Graphics.hpp>

using std::cin;
using std::cout;
using std::endl;




class Tear
{
public:
    float live_time;
    float speed;
    Vector2D coord;
    sf::Texture texture;
    sf::Sprite sprite;
public:


    Vector2D getVelocity();
    float getMaxSpeed();
    int getHealth();
    Vector2D getCoord();
    sf::Sprite getSprite();

    virtual void turn();




};
