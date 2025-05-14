#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "map.cpp"
typedef std::vector<std::vector<char>> Vec2D;
sf::View view;
sf::RenderWindow window;

float x = 3600; // Координаты центра
float y = 3600;

sf::View getCordsForView(float x, float y){
    float viewX = x;
    float viewY = y;
    view.setCenter(viewX, viewY);
    // std::cout << viewX;
    view.setSize(1000, 600);
    view.zoom(0.77);
    return view;
};
