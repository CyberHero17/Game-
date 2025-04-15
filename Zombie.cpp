#include "Zombie.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Structures.hpp"

Zombie::Zombie(int hp, float max_speed, sf::Texture texture)
{
    this->name = "Zombie";
    this->acceleration = max_speed * 4;
    this->health = hp;
    this->max_speed = max_speed;
    this->texture = texture;
    this->sprite.setTexture(this->texture);
    this->coord = {500, 200};

}

Zombie::Zombie()
{
    this->name = "Zombie (default)";
    this->acceleration = 4;
    this->health = 5;
    this->max_speed = 1;
    this->sprite.setTexture(this->texture);
    this->coord = {500, 200};
}


void Zombie::MoveWithoutIntertion(Player& pl)
{
    float time = 1;
    //cout << "Zombie's turn" << endl;
    Vector2D vect_to_player = this->coord - pl.coord;
    float Abs_vect_to_player = sqrt(vect_to_player.ModuleQuadr());

    //cout << "vect_to_player = " << vect_to_player.x << " " << vect_to_player.y << endl; 
    if(Abs_vect_to_player > 10)
    {
        velocity = -max_speed/Abs_vect_to_player * vect_to_player;
    }
    else
    velocity = {0,0};


    this->coord = this->coord + this->velocity * time;
    this->sprite.setPosition({this->coord.x, this->coord.y} );
    
}

int Zombie::turn(Player& pl)
{
    if(this->getHealth() <= 0)
    {
        return 0; // зомби умер
    }
    else
    {
        MoveWithoutIntertion(pl);
        if ( (this->coord - pl.coord).ModuleQuadr() < 110)
        {
            pl.getDamage(1);
        }
        return 1;
    }

}

void Zombie::death()
{
    cout << "Player is dead" << endl;
}