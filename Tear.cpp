#include "Tear.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>




Tear::Tear()
{
    this->damage = 2;
    this->live_time = 10;
    this->max_speed = 5;
    this->texture.loadFromFile("Textures/Tear.png");
    this->sprite.setTexture(this->texture);
    this->coord = coord;
    

    cout << "Default tear constructor\n";
    velocity = {max_speed, 0};

}

Tear::Tear(Vector2D coord, sf::Event event)
{
    this->damage = 2;
    this->live_time = 10;
    this->max_speed = 5;
    this->texture.loadFromFile("Textures/Tear.png");
    this->sprite.setTexture(this->texture);
    this->coord = coord;
    
    if (event.type == sf::Event::KeyPressed)
    {
        if (     sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) velocity = {-max_speed, 0};
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velocity = {max_speed, 0};
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) velocity = {0, max_speed};
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) velocity = {0, -max_speed};
    }
    else
    {
        cout << "Button wasn't pressed\n";
        velocity = {max_speed, 0};
    }
    cout << "Tear created\n";

}

int Tear::turn(list<Entity> &Mosters)
{

    this->coord.x = this->coord.x + this->velocity.x;
    this->coord.y = this->coord.y + this->velocity.y;
    for(auto it = Mosters.begin(); it != Mosters.end(); ++it)
    {
                                                    //cout << it->getCoord() << endl;
        if ( (it->getCoord() - this->getCoord()).ModuleQuadr() <= 10000 )
        {
            it->getDamage(this->damage);
            return 0; // 0 - означает, что слеза врезалась во что то и ее надо убрать в цикле в main.cpp
        }
    }
    this->sprite.setPosition({this->coord.x, this->coord.y} );
    return 1;
}

Vector2D Tear::getCoord()
{
    return this->coord;
}

sf::Sprite Tear::getSprite()
{
    return this->sprite;
} 
