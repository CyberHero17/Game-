#include "Zombie.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

Zombie::Zombie(int hp, float max_speed, sf::Texture texture)
{
    this->acceleration = max_speed * 4;
    this->health = hp;
    this->max_speed = max_speed;
    this->texture = texture;
    this->sprite.setTexture(this->texture);
    this->coord = {500, 200};

}

Zombie::Zombie()
{
    this->acceleration = 4;
    this->health = 5;
    this->max_speed = 1;
    this->sprite.setTexture(this->texture);
    this->coord = {500, 200};
}


void Zombie::MoveWithoutIntertion(Player& pl)
{
    //cout << "Zombie's turn" << endl;
    Vector2D vect_to_player = this->coord - pl.coord;
    float Abs_vect_to_player = sqrt(vect_to_player.x * vect_to_player.x + vect_to_player.y * vect_to_player.y);

    //cout << "vect_to_player = " << vect_to_player.x << " " << vect_to_player.y << endl; 
    if(Abs_vect_to_player > 1)
    {
        velocity.x = -max_speed * vect_to_player.x/Abs_vect_to_player;
        velocity.y = -max_speed * vect_to_player.y/Abs_vect_to_player;
    }
    else
    velocity = {0,0};


    this->coord.x = this->coord.x + this->velocity.x;
    this->coord.y = this->coord.y + this->velocity.y;
    this->sprite.setPosition({this->coord.x, this->coord.y} );
}

void Zombie::turn(Player& pl)
{
    MoveWithoutIntertion(pl);
}

void Zombie::death()
{
    cout << "Player is dead" << endl;
}

void Zombie::getDamage(int D)
{
    health -= D;
    cout << "Got " << D << " damage\n";
}