#pragma once 
#include "map.hpp"
Object::Object(){
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    objRect = sf::FloatRect(0,0,0,0);
};
Object::Object(float X, float Y, float W, float H){
    x = X;
    y = Y;
    width = W;
    height = H;
    objRect = sf::FloatRect(x, y, width, height);
};

void Object::setName(std::string n){
    this->name = n;
};
float Object::getX(){
    return this->x;
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

void Object::setX(float x){
    this->x = x;
}
void Object::setY(float y){
    this->y = y;
}
void Object::setWidth(float w){
    this->width = w;
}
void Object::setHeight(float h){
    this->height = h;
}

std::string Object::getName(){
    return this->name;
};
void Object::setRect(sf::FloatRect f){
    this->objRect = f;
};
sf::FloatRect& Object::getRect(){
    
    return this->objRect;
};

Door::Door(std::string filename){

    texture.loadFromFile(filename);
    sprite.setTexture(texture);
};

bool Object::CheckCollision(sf::FloatRect& heatbox){
    std::cout << "I'm object";
    return this->getRect().intersects(heatbox);
};

bool Door::CheckCollision(sf::FloatRect& d){
    //std::cout << '{'<< this->getRect().getSize().x << ", " << this->getRect().getSize().y << '}';
    return this->getRect().intersects(d);
};

sf::Sprite& Object::getSprite(){
    sf::Sprite sp;
    return sp;
};

sf::Sprite& Door::getSprite(){
    //std::cout << "I'm from door";
    return this->sprite;
};

Room::Room(int ID){ // Пустая карта 
    X = 0;
    Y = 0;
    width = 0;
    height = 0;
    id = ID;
}
std::vector<Object*>& Room::getObj(){
    return obj;
};
int Room::getHeight(){
    return height;
};
int Room::getWidth(){
    return width;
};
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
int Room::getRoomId(){
    return id;
};

bool Room::CreateObjects(){

    std::string strg1 = "Textures/TypesOfRooms/";
    char Id = id + 48;
    std::string strg = strg1 + Id + ".tmx";
    tinyxml2::XMLDocument data;
    data.LoadFile(strg.c_str());
    tinyxml2::XMLNode* root = data.FirstChild();
    if(!root){
        std::cout << "Empty file";
        return false;
    }
    //std::cout << root;
    tinyxml2::XMLElement* m = data.FirstChildElement("map");
    tinyxml2::XMLElement* og = m->FirstChildElement("objectgroup"); 
    tinyxml2::XMLElement* o = og->FirstChildElement("object");
    //Считаем объекты 
    while(o){
        float Xo = strtof(o->Attribute("x"), NULL) + this->X;
        float Yo = strtof(o->Attribute("y"), NULL) + this->Y;
        float WIDTH = strtof(o->Attribute("width"), NULL);
        float HEIGHT = strtof(o->Attribute("height"), NULL);
        
        std::string Name = "none";
        if(o->Attribute("name") != nullptr){
            Name = (std::string)(o->Attribute("name"));
        } 

        if(Name[0] != 's'){
            Object* item = new Door(std::move("Textures/Door.png"));
            item->setX(Xo);
            item->setY(Yo);
            item->setWidth(WIDTH);
            item->setHeight(HEIGHT);
            item->setRect(sf::FloatRect(Xo, Yo, WIDTH, HEIGHT));
            item->setName(Name);
            this->obj.push_back(item);
            o = o->NextSiblingElement("object");
            
            continue;
        }
        
        Object* item = new Object(Xo, Yo, WIDTH, HEIGHT);
        item->setName(Name);
        this->obj.push_back(item);
        o = o->NextSiblingElement("object");
    };
    //std::cout << obj[obj.size()-1]->getName();
    std::cout << "Object ----> Success";
    return true;
};


bool Room::PlaceDoors(){
    //std::cout << this->getLayers().size();
    for(auto& x : this->getObj()){
        if(x->getName()[0] == 's') continue;
        sf::Sprite scopy = x->getSprite();
        float Wid = x->getWidth();
        float Hei = x->getHeigth();
        float Xr = x->getX();
        float Yr = x->getY();
        //std::cout << Xr << ' ' << Yr;
        if(x->getName() == "ldoor"){
            scopy.setPosition(Xr, Yr + Hei);
            scopy.rotate(-90);
            std::cout << Xr << "," << Yr;
            this->layers.push_back(scopy);
        }
        if(x->getName() == "rdoor"){
            scopy.setPosition(Xr+Wid, Yr);
            scopy.rotate(90);
            this->layers.push_back(scopy);
        }
        if(x->getName() == "udoor"){
            scopy.setPosition(Xr+Wid, Yr);
            this->layers.push_back(scopy);
        }
        if(x->getName() == "ddoor"){
            scopy.setPosition(Xr + Wid, Yr + 1.38f*Hei);
            scopy.rotate(180);
            this->layers.push_back(scopy);
        }
    }
    //std::cout << '\n' << this->getLayers().size();
    return true;
};

void Room::CreateRoom(Room* ptrr, float x, float y){
    
    std::string strg1 = "Textures/TypesOfRooms/";
    char Id = id + 48;
    
    std::string strg = strg1 + Id + ".tmx";
    //std::cout << strg;
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



    tinyxml2::XMLElement* tileset;
    tileset = mptr->FirstChildElement("tileset");
    std::string TISource = tileset->Attribute("source"); // Map Image source 
    
   //======== Open *.tsx
    tinyxml2::XMLDocument tileMapsource;
    tileMapsource.LoadFile(((strg1 + TISource).c_str()));

    tinyxml2::XMLElement* maptile = tileMapsource.FirstChildElement("tileset");
    
    tinyxml2::XMLElement* ptrI;
    ptrI = maptile->FirstChildElement("image"); // Указываем на Image 
    
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
    int firstgid = atoi(Tptr->Attribute("firstgid"));                                               // Айдишник первого элемента
    std::string ObjectImSource = strg1 + Tptr->Attribute("source");

    // open file with images of objects properties
    tinyxml2::XMLDocument rocks;
    rocks.LoadFile(ObjectImSource.c_str()); 
    tinyxml2::XMLElement* im = rocks.FirstChildElement("tileset")->FirstChildElement("image");

    if(!TextureRocks.loadFromFile(strg1 + (std::string)im->Attribute("source"))){
        std::cout << "CANT DOWNLOAD TEXTURE";
        return;
    };
    
    // Ширина и высота картинки с тайлами в пикселях 
    int width = atoi(im->Attribute("width")); 
    int height = atoi(im->Attribute("height"));
    
    tinyxml2::XMLElement* plr;
    plr = mptr->FirstChildElement("layer");
    while((std::string)plr->Attribute("name") != "Tile Layer 2"){
        plr = plr->NextSiblingElement("layer");
    }

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
    CreateObjects();
    PlaceDoors();
    std::cout << "Success ---->"<< id << '\n';
};


std::vector<sf::Sprite>& Room::getLayers(){
    return layers;
}

void Room::Draw(sf::RenderWindow& window){ 
    window.draw(this->sprite);
    for(int i = 0; i < static_cast<int>(layers.size()); ++i){
        window.draw(layers[i]);                                             // все натыканные элементы на картe
        //std::cout << layers[i].getTexture()->getSize().x<<'\n';
    }
};