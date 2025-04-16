#pragma once

#include <iostream>
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
#include <list>
#include "Tear.hpp"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::string;

class Tear;
class Player: public Entity
{
public:
    float range;

    float time_betweenshoots;
    float time_invicibility;

    sf::Sprite BodySprite;
    sf::Sprite HeadSprite;
    string BodyDirection;
    string HeadDirection;
    sf::Clock tears_time;
    sf::Clock damage_time;
    sf::Clock body_time;

    vector<sf::Sprite> BodyAnimationSprites;

    Player(int hp, float speed, float range);
    void MoveInertion(sf::Event event);
    void MoveWithoutIntertion(sf::Event event);
    void shoot(sf::Event event, list<Tear>& Tears);
    void turn(sf::Event event, bool EnableIntertion, list<Tear>& Tears);
    void death();
    void getDamage(int D);

    ~Player() {};
};











