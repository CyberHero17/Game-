#pragma once

#include <iostream>
#include "Player.hpp"
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
#include <list>


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::list;
class Player;
class Tear;
class Zombie: public Entity
{
public:
    Vector2D dV;
    string BodyDirection;
    sf::Sprite BodySprite;
    sf::Sprite HeadSprite;
    sf::Clock body_time;
    vector<sf::Sprite> BodyAnimationSprites;

    Zombie(int hp, float speed, Vector2D coord);


    void MoveInertion(Player& pl);
    int turn(Player& pl, list<Zombie>& Zombies);
    void getDamage(Tear& t);
    void death();


    ~Zombie() {};
};