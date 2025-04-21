#pragma once
#include <iostream>
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Player.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


class Item
{
public:
    bool ispicked;

    sf::Sprite PedestalSprite;
    sf::Sprite ItemSprite;
    int id;
    string name;
    sf::Clock AnimationTime;
    Vector2D coord;
    float collider_size;

    virtual void pick(Player& pl);
    virtual void draw(sf::RenderWindow& window);
    virtual void turn(Player& pl);
};