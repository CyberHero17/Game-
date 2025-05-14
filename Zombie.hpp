#pragma once

#include <iostream>
#include "Player.hpp"
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
#include <list>
#include "map.hpp"

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

    float SizeX, SizeY;
    Vector2D dV;
    string BodyDirection;
    sf::Sprite BodySprite;
    sf::Sprite HeadSprite;
    sf::Clock body_time;
    vector<sf::Sprite> BodyAnimationSprites;

    Zombie(int hp, float speed, Vector2D coord);


    void MoveInertion(Player& pl, vector<Room*>& rooms);
    int turn(Player& pl, list<Zombie>& Zombies, vector<Room*>& rooms);
    void getDamage(Tear& t);
    void death();


    ~Zombie() {};
};