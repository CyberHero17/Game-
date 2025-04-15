#include <iostream>
#include "Entity.hpp"
//#include <SFML/Graphics.hpp>

using std::cin;
using std::cout;
using std::endl;

void Entity::death()
{
    cout << "Entity Dead" << endl;
}

void Entity::turn()
{
    cout << "Entity's turn" << endl;
}

void Entity::getDamage(int D)
{
    this->health -= D;
    cout << this->name << " got " << D << " damage" << endl;
}
Vector2D Entity::getVelocity()
{
    return velocity;
}

float Entity::getMaxSpeed()
{
    return max_speed;
}

int Entity::getHealth()
{
    return health;
}
Vector2D Entity::getCoord()
{
    return coord;
}

sf::Sprite Entity::getSprite()
{
    return sprite;
}
