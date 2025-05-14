#pragma once

#include <iostream>
#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
#include <list>
#include "Tear.hpp"
#include <string>
#include "map.hpp"

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
    int HPContCount;
    /*обьявлена в Entity*/                    sf::Text max_speed_Text;
    float Damage;       sf::Text DamageText;
    float TearsFreq;    sf::Text TearsFreqText; // скорострельность
    float Range;        sf::Text RangeText;
    float ShotSpeed;    sf::Text ShotSpeedText;
    float Luck;         sf::Text LuckText;

    float DevilChance; sf::Text DevilChanceText;
    float AngelChance; sf::Text AngelChanceText;

    float TearMass;
    float time_invicibility;
    
    std::string roomId = "0";

    sf::Texture CharacteristicsTexture;
    sf::Sprite CharacteristicsSprite;

    sf::Sprite BodySprite;
    sf::Sprite HeadSprite;
    sf::Sprite GettingItemSprite;
    sf::Sprite GettingDamageSprite;

    string BodyDirection;
    string HeadDirection;
    sf::Clock tears_time;
    sf::Clock damage_time;
    sf::Clock body_time;
    sf::Clock GettingItemTime;


    bool GettingItem;
    list<sf::Sprite> HealthConteiners; 
    list<sf::Sprite> HealthHearts; 
    
    vector<sf::Sprite> BodyAnimationSprites;

    float SizeX, SizeY;

    Player(int hp, float max_speed, float Damage, float TearsFreq, float Range, float ShotSpeed, float Luck, float TearMass);
    void MoveInertion(sf::Event event, vector<Room*>& rooms);

    void shoot(sf::Event event, list<Tear>& Tears);
    void turn(sf::Event event, bool EnableIntertion, list<Tear>& Tears, vector<Room*>& rooms);
    void death();
    void getDamage(int D);
    void draw(sf::RenderWindow& window);

    ~Player() {};
};











