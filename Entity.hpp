#pragma once
#include <iostream>
#include "Structures.cpp"
#include <SFML/Graphics.hpp>

using std::cin;
using std::cout;
using std::endl;

class Entity
{
public:
    float acceleration;
    int health;
    Vector2D velocity;
    float max_speed;
    Vector2D coord;
    sf::Texture texture;
    sf::Sprite sprite;
public:

    Vector2D getVelocity();
    float getMaxSpeed();
    int getHealth();
    Vector2D getCoord();
    sf::Sprite getSprite();
    ~Entity() {};

    virtual void death();
    virtual void turn();
    virtual void getDamage(int D);
};
