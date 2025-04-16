#include "Tear.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>




Tear::Tear()
{
    this->time.restart();
    this->damage = 2;
    this->range = 10;
    this->max_speed = 5;
    this->texture.loadFromFile("Textures/Tear.png");
    this->sprite.setTexture(this->texture);
    this->coord = coord;
    

    cout << "Default tear constructor\n";
    velocity = {max_speed, 0};

}

Tear::Tear(Vector2D coord, sf::Event event, float range, string HeadDirection)
{
    this->time.restart();
    this->damage = 2;
    this->range = range;
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
        else
        {
            cout << "Button wasn't pressed\n";
            velocity = {max_speed, 0};
        }

    }


}

int Tear::turn(list<Zombie> &Zombies)
{
    this->coord.x = this->coord.x + this->velocity.x;
    this->coord.y = this->coord.y + this->velocity.y;
    float time_of_living = time.getElapsedTime().asSeconds();
    if( time_of_living > this->range/this->max_speed)
    {
        return 2; // означает что слеза пропала т.к. изжила свое время
    }

    for(auto it = Zombies.begin(); it != Zombies.end(); ++it)
    {
        if ( (it->getCoord() - this->getCoord()).ModuleQuadr() <= 1000 )
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


std::ostream &operator<<(std::ostream &os, const Tear &t)
{
    os << "Tear's coodr = " << t.coord << endl;
    os << "Tear's max_speed = " <<  t.max_speed << endl;
    os << "Tear's velocity = " << t.velocity;
    return os;
}
