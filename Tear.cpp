#include "Tear.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>




Tear::Tear()
{
    this->time.restart();
    this->mass = 1;
    this->Damage = 2;
    this->Range = 10;
    this->ShotSpeed = 5;
    this->texture.loadFromFile("Textures/Tear.png");
    this->sprite.setTexture(this->texture);
    this->coord = coord;
    

    cout << "Default tear constructor\n";
    velocity = {ShotSpeed, 0};

}

Tear::Tear(Vector2D coord, sf::Event event, string HeadDirection, float Damage, float Range, float ShotSpeed, float mass)
{
    this->Damage = Damage;
    this->Range = Range;
    this->ShotSpeed = ShotSpeed;
    
    this->mass = mass;
    Animation = 0;
    this->time.restart();
    
    
    
    this->texture.loadFromFile("Textures/Tear.png");
    this->sprite.setTexture(this->texture);
    
    
    
    if (event.type == sf::Event::KeyPressed)
    {
        if (     sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
        {
            velocity = {-ShotSpeed, 0};
            this->coord = {coord.x-16, coord.y - 12};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
        {
            velocity = {ShotSpeed, 0};
            this->coord = {coord.x + 32 - 8, coord.y - 12};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
        {
            velocity = {0, ShotSpeed};
            this->coord = {coord.x , coord.y + 16 - 4};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
        {
            velocity = {0, -ShotSpeed};
            this->coord = {coord.x , coord.y + 4};
        }

        else
        {
            cout << "Button wasn't pressed\n";
            velocity = {ShotSpeed, 0};
        }
    }


}

int Tear::turn(list<Zombie> &Zombies)
{
    if(not Animation)
    {
        this->coord.x = this->coord.x + this->velocity.x;
        this->coord.y = this->coord.y + this->velocity.y;
        float time_of_living = time.getElapsedTime().asSeconds();
        if( time_of_living > this->Range/this->ShotSpeed)
        {
            this->death();
            return 3; // означает что слеза пропала т.к. изжила свое время
        }
    
        for(auto it = Zombies.begin(); it != Zombies.end(); ++it)
        {
            if ( (it->getCoord() - this->getCoord()).ModuleQuadr() <= 1000 )
            {
                it->getDamage(*this);
                this->death();
                return 3; // 3 - означает что пора запускать анимацию уничтожения
            }
        }
        this->sprite.setPosition({this->coord.x, this->coord.y} );
        return 1;
    }
    else
    {
        int time_elapsed_from_death = animation_time.getElapsedTime().asMilliseconds();
        this->texture.loadFromFile("Textures/TearAnimationTextures.png");
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(this->coord.x, this->coord.y);
        if( time_elapsed_from_death <  400)
        {
            this->sprite.setTextureRect(sf::IntRect( (time_elapsed_from_death/80)%5 * 64 ,0,64,64));
            
            
            return 1;
        }
        else return 0; // 0 - означает, что слеза завершила анимацию уничтожения и ее надо убрать в цикле в main.cpp

        
    }
    

}

Vector2D Tear::getCoord()
{
    return this->coord;
}

sf::Sprite Tear::getSprite()
{
    return this->sprite;
}

void Tear::death()
{
    this->Animation = 1;
    animation_time.restart();

    this->Range = Range;
    this->ShotSpeed = 0;
    velocity = {0,0};
}

std::ostream &operator<<(std::ostream &os, const Tear &t)
{
    os << "Tear's coodr = " << t.coord << endl;
    os << "Tear's ShotSpeed = " <<  t.ShotSpeed << endl;
    os << "Tear's velocity = " << t.velocity;
    return os;
}
