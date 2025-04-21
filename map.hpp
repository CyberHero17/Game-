#pragma once 
#include <SFML/Graphics.hpp> 
#include <iostream> 
#include <vector>
#include <map> 
#include <string>
#include "tinyxml2.h"
#include "tinyxml2.cpp"

class Object{
private:
    std::string name; 
    float x, y, width, height; 
    sf::Texture textureObj; // Текстурка объекта
    sf::Sprite spriteObj;
public: 
    float getX();
    float getY();
    float getWidth();
    float getHeigth();
    std::string getName();
    sf::Sprite getSpriteObj();
    void setSpriteTexture(sf::Texture tex);
    //void setSpriteObj(sf::Sprite ob);
    void setTextureObj(std::string filename); // Установить текстурку объекта
};

class Room{

//friend class Object;
private:
    int mobs;
    int width, height; // Размер картинки карты в пикселях  
    float X, Y;// Координаты спрайта 
    sf::Texture texture;
    sf::Texture TextureRocks;
    sf::Sprite sprite;
    std::vector<Object> obj; // Все дополнительные элементы на карте
    std::vector<sf::Sprite> layers; // Все дополнительные изображения
public:
    Room();
    std::vector<Object> getPtrObj(); // Указатель на вектор obj
    void LoadTextureFromFile(std::string filename);
    void setSpriteTexture();
    void Draw(sf::RenderWindow& window);
    void CreateRoom(std::string idRoom/*Номер комнаты в строке*/, Room* ptrr, float x, float y); // Создание комнаты с таким айдишником (Это основная функция)
    bool CreateObjects(Room* ptrr, float x, float y); // x, y - начальные координаты комнаты 
    sf::Sprite getMapSprite();
    sf::Texture getMapTexture();
};
//std::map<int, Room> rooms; // Тут будут все комнаты

void Object::setTextureObj(std::string filename){
    this->textureObj.loadFromFile(filename);
};
float Object::getX(){
    return this->x;
};
std::vector<Object> Room::getPtrObj(){
    return obj;
};
float Object::getY(){
    return this->y;
};
float Object::getWidth(){
    return this->width;
}; 
float Object::getHeigth(){
    return this->height;
};
std::string Object::getName(){
    return this->name;
};

sf::Sprite Object::getSpriteObj(){
    return this->spriteObj;
};
void Object::setSpriteTexture(sf::Texture tex){
    this->spriteObj.setTexture(textureObj);
};

//=============================
Room::Room(){ // Пустая карта 
    X = 0;
    Y = 0;
    width = 0;
    height = 0;
    mobs = 0;
}
void Room::LoadTextureFromFile(std::string filename){
    this->texture.loadFromFile(filename);
};
void Room::setSpriteTexture(){
    this->sprite.setTexture(this->texture);
};
sf::Sprite Room::getMapSprite(){
    return this->sprite;
};
sf::Texture Room::getMapTexture(){
    return this->texture;
};

void Room::CreateRoom(std::string Id, Room* ptrr, float x, float y){
    
    std::string strg1 = "Textures/TypesOfRooms/";
    
    std::string strg = strg1 + Id + ".tmx";

    tinyxml2::XMLDocument data;
    data.LoadFile(strg.c_str());
    tinyxml2::XMLNode* root = data.FirstChild();
    if(root == nullptr){
        std::cout << "Empty file";
        return;
    }

    tinyxml2::XMLElement* mptr = data.FirstChildElement("map");
    if(!mptr) std::cout << "smth";
    ptrr->width = atoi(mptr->Attribute("width")); // Размер карты в тайлах
    ptrr->height = atoi(mptr->Attribute("height"));

    // int tilemapwidth = atoi(data.FirstChildElement("map")->Attribute("width"));
    // int tilemapheight = atoi(data.FirstChildElement("map")->Attribute("height"));

    tinyxml2::XMLElement* tileset;
    tileset = mptr->FirstChildElement("tileset");
    std::string TISource = tileset->Attribute("source"); // Map Image source 
    //std::cout << TISource;
   //======== Open *.tsx
    tinyxml2::XMLDocument tileMapsource;
    tileMapsource.LoadFile(((strg1 + TISource).c_str()));

    tinyxml2::XMLElement* maptile = tileMapsource.FirstChildElement("tileset");
    
    tinyxml2::XMLElement* ptrI;
    ptrI = maptile->FirstChildElement("image"); // Указываем на Image 
    //ptrr->width = atoi(ptrI->Attribute("width")); // 720
    //ptrr->height = atoi(ptrI->Attribute("height"));
    const std::string imagepath = strg1 + (std::string)ptrI->Attribute("source");
    if(!ptrr->texture.loadFromFile(imagepath)){
        std::cout << "SMTH WRONG WITH IMAGE of MAP";
        return;
    }
    ptrr->sprite.setTexture(ptrr->texture); // Создаём спрайт карты
    ptrr->sprite.setPosition(x, y);
    ptrr->X = x;
    ptrr->Y = y;
    // till this moment texture of room if already downloaded 
    // Work with objects on map 

   
    tinyxml2::XMLElement* Tptr = mptr->FirstChildElement("tileset")->NextSiblingElement("tileset"); // Указываем на файлик с картинками тайлов
    int firstgid = atoi(Tptr->Attribute("firstgid"));  // Айдишник первого элемента
    std::string ObjectImSource = strg1 + Tptr->Attribute("source");

    // open file with images of objects properties
    tinyxml2::XMLDocument rocks;
    rocks.LoadFile(ObjectImSource.c_str()); 
    tinyxml2::XMLElement* im = rocks.FirstChildElement("tileset")->FirstChildElement("image");

    if(!TextureRocks.loadFromFile(strg1 + (std::string)im->Attribute("source"))){
        std::cout << "CANT DOWNLOAD TEXTURE";
        return;
    };
    //sf::Sprite SpriteRocks;
    //SpriteRocks.setTexture(TextureRocks);
    
    // Ширина и высота картинки с тайлами в пикселях 
    int width = atoi(im->Attribute("width")); 
    int height = atoi(im->Attribute("height"));
    //std::cout << width;
    // Далее ищем по указателю нужный слой (Tile Layer 2)
    tinyxml2::XMLElement* plr;
    plr = mptr->FirstChildElement("layer");
    while((std::string)plr->Attribute("name") != "Tile Layer 2"){
        plr = plr->NextSiblingElement("layer");
    }
    //std::cout << (std::string)(plr->Attribute("name"));
    //=================== Далее создаём первую половину всех объектов на карте - их изображения
    std::vector<sf::Sprite> v;
    TextureRocks.setSmooth(true);
    for(unsigned int i = 0; i < TextureRocks.getSize().y / 32; ++i)
        for(unsigned int j = 0; j < TextureRocks.getSize().x / 32; ++j){
            sf::Sprite spr;
            spr.setTexture(TextureRocks);
            spr.setTextureRect(sf::IntRect(j*32, i*32, 32, 32));
            v.push_back(spr);
        }
    
    // till this moment all the textures is set    
    // now we should create and place all the objects 
    // Сначала картинки, затем объекты solid
    tinyxml2::XMLElement* ptl = plr->FirstChildElement("data")->FirstChildElement("tile");
    for(int i = 0; i < ptrr->height; ++i)
        for(int j = 0; j < ptrr->width; ++j){
            if(ptl->Attribute("gid") == nullptr){
                ptl = ptl->NextSiblingElement("tile");
                continue;
            }
            int num = atoi(ptl->Attribute("gid")) - firstgid;
            v[num].setPosition(x + 16*j, y + 16*(i-1));
            layers.push_back(v[num]);
            ptl = ptl->NextSiblingElement("tile");
        }   
    // Всё, есть спрайты всех объектов на карте
    std::cout << "Success" + Id << '\n';
/**/}
void Room::Draw(sf::RenderWindow& window){ 
    window.draw(this->sprite);
    for(int i = 0; i < static_cast<int>(layers.size()); ++i)
        window.draw(layers[i]);  
};