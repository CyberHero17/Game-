#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "map.hpp"
sf::View view;
sf::RenderWindow window;
Room r1;
Room* ptr = &r1;
std::string Id = "7";
float x = 0;
float y = 0;
sf::View getCordsForView(float x, float y){
    float viewX = x;
    float viewY = y;
    view.setCenter(/*r1.getMapSprite().getPosition().x + r1.getMapTexture().getSize().x/2*/ viewX, /*r1.getMapSprite().getPosition().y + r1.getMapTexture().getSize().y/2*/ viewY);
    
    // std::cout << viewX;
    view.setSize(1000, 600);
    view.zoom(0.77);
    return view;
}
