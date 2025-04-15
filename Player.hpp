#pragma once

#include <iostream>
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
#include <list>
#include "Tear.hpp"

//#include "Tear.hpp" // нельзя ибо получается замкнутный круг из include ?

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::list;

class Tear;
class Player: public Entity
{
public:
    sf::Clock clock;
    Player(int hp, float speed, sf::Texture texture);
    Player();
    void MoveInertion(sf::Event event);
    void MoveWithoutIntertion(sf::Event event);
    void shoot(sf::Event event, list<Tear>& Tears);
    void turn(sf::Event event, bool EnableIntertion, list<Tear>& Tears);
    void death();
    void getDamage(int D);
    ~Player() {};
};












