#pragma once 
#include <SFML/Graphics.hpp> 
#include <iostream> 
#include <vector>
#include <map> 
#include "Player.hpp"
#include <string>
#include "tinyxml2.h"
//#include "tinyxml2.cpp"
class Player;

class Object{
friend class Room;
private:
    std::string name; 
    float x, y, width, height; 
    sf::FloatRect objRect;
public: 
    Object(float X, float Y, float W, float H);
    Object();

    float getX();
    float getY();
    float getWidth();
    float getHeigth();

    void setX(float x);
    void setY(float y);
    void setWidth(float w);
    void setHeight(float h);

    sf::FloatRect& getRect();
    void setRect(sf::FloatRect f);
    std::string getName();
    virtual bool CheckCollision(sf::FloatRect& pl); // Реализацию сюда
    virtual sf::Sprite& getSprite();
    void setName(std::string n);
};

class Room{
friend class Object;
private:
    std::string id;
    int width, height;                                                  // Размер картинки карты в пикселях  
    float X, Y;                                                         // Координаты спрайта 
    sf::Texture texture;
    sf::Texture TextureRocks;
    sf::Sprite sprite;
    //std::vector<Door> doors;
    std::vector<Object*> obj;                                           // Все дополнительные элементы на карте
    std::vector<sf::Sprite> layers;                                     // Все дополнительные изображения
public:
    Room(std::string ID);
    void Draw(sf::RenderWindow& window);
    void CreateRoom(Room* ptrr, float x, float y);                      // Создание комнаты с таким айдишником (Это основная функция)
    bool CreateObjects();                                               // x, y - начальные координаты комнаты. Ставим объекты, но не отрисовываем их 
    void Teleport(Player& p);
    bool PlaceDoors();                                                  // Расставляем картинки дверей 
    
    // гетеры, сетеры
    std::vector<Object*>& getObj(); // вектор obj
    //std::vector<Door>& getDoors(); // вектор doors
    void LoadTextureFromFile(std::string filename);
    void setSpriteTexture();
    std::vector<sf::Sprite>& getLayers();

    int getWidth();
    int getHeight();
    sf::Sprite getMapSprite();
    sf::Texture getMapTexture();
    char getRoomId();
};


class Door : public Object{
private: 
    std::string name; 
    float x, y, width, height; 
    sf::FloatRect objRect;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Door(std::string filename);
    sf::Sprite& getSprite();
    bool CheckCollision(sf::FloatRect& d);    
};