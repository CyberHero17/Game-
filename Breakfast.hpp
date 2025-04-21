#pragma once

#include "Item.hpp"

class Breakfast : public Item
{
public:
    sf::Clock PickedTime;

    Breakfast(Vector2D coord);
    void pick(Player& pl) override;
    void draw(sf::RenderWindow& window) override;
    void turn(Player &pl) override;
};