#pragma once 
#include <SFML/Graphics.hpp> 
#include <iostream> 
#include <vector>
#include <map> 
#include <string>
#include "tinyxml2.h"
#include "tinyxml2.cpp"

class Object{
friend class Room;
friend bool CheckCollision(sf::FloatRect& head, sf::FloatRect& slave);
private:
    std::string name; 
    float x, y, width, height; 
    sf::FloatRect objRect;
public: 
    Object(float X, float Y, float W, float H);
    float getX();
    float getY();
    float getWidth();
    float getHeigth();
    std::string getName();
    void setName(std::string n);
};

class Room{

//friend class Object;
private:
    std::string id;
    int width, height; // Размер картинки карты в пикселях  
    float X, Y;// Координаты спрайта 
    sf::Texture texture;
    sf::Texture TextureRocks;
    sf::Sprite sprite;
    std::vector<Object> obj; // Все дополнительные элементы на карте
    std::vector<sf::Sprite> layers; // Все дополнительные изображения
public:
    Room(std::string ID);
    void Draw(sf::RenderWindow& window);
    void CreateRoom(Room* ptrr, float x, float y); // Создание комнаты с таким айдишником (Это основная функция)
    bool CreateObjects(); // x, y - начальные координаты комнаты. Ставим объекты, но не отрисовываем их 

    // гетеры, сетеры
    std::vector<Object> getObj(); // вектор obj
    void LoadTextureFromFile(std::string filename);
    void setSpriteTexture();

    sf::Sprite getMapSprite();
    sf::Texture getMapTexture();
    char getRoomId();
};