#include "Zombie.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Structures.hpp"

Zombie::Zombie(int hp, float max_speed, Vector2D coord)
{
    dV = {0,0};
    BodyDirection = "Down";
    this->mass = 3;
    this->name = "Zombie";
    this->acceleration = max_speed/20;
    this->health = hp;
    this->max_speed = max_speed;
    this->texture = texture;

    this->coord = coord;

    this->texture.loadFromFile("Textures/Zombie_textures.png");
    this->HeadSprite.setTexture(this->texture);
    this->HeadSprite.setTextureRect(sf::IntRect(0,0,32,32));
    this->HeadSprite.setScale(2,2);
    
    this->BodySprite.setTexture(this->texture);
    this->BodySprite.setTextureRect(sf::IntRect(0,32,32,32));
    this->BodySprite.setScale(2,2);

    sf::Sprite temp; 
    temp.setTexture(this->texture);
    temp.setPosition(this->coord.x, this->coord.y);
    temp.scale(2,2); 

    temp.setTextureRect(sf::IntRect(192,0,32,32));   BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(224,0,32,32));   BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(0,32,32,32));    BodyAnimationSprites.push_back(temp); // кадры ходьбы вперед
    temp.setTextureRect(sf::IntRect(32,32,32,32));   BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(64,32,32,32));   BodyAnimationSprites.push_back(temp); // с 0 по 9 индекс
    temp.setTextureRect(sf::IntRect(96,32,32,32));   BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(128,32,32,32));  BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(160,32,32,32));  BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(192,32,32,32));  BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(224,32,32,32));  BodyAnimationSprites.push_back(temp);
    

    temp.setTextureRect(sf::IntRect(0,64,32,32));    BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(32,64,32,32));   BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(64,64,32,32));   BodyAnimationSprites.push_back(temp);// кадры ходьбы вправо
    temp.setTextureRect(sf::IntRect(96,64,32,32));   BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(128,64,32,32));  BodyAnimationSprites.push_back(temp); // с 10 по 19 индекс
    temp.setTextureRect(sf::IntRect(160,64,32,32));  BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(192,64,32,32));  BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(224,64,32,32));  BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(0,96,32,32));    BodyAnimationSprites.push_back(temp);
    temp.setTextureRect(sf::IntRect(32,96,32,32));   BodyAnimationSprites.push_back(temp);

}





void Zombie::MoveInertion(Player &pl)
{
    float time = 1;
    this->dV = {0,0};
    //cout << "Zombie's turn" << endl;
    Vector2D vect_to_player = this->coord - pl.coord;
    float Abs_vect_to_player = sqrt(vect_to_player.ModuleQuadr());


    int BodyAnimationTime = this->body_time.getElapsedTime().asMilliseconds();

    //cout << "vect_to_player = " << vect_to_player.x << " " << vect_to_player.y << endl; 

    if (Abs_vect_to_player != 0)  this->dV = -acceleration/Abs_vect_to_player * vect_to_player;
    velocity = velocity + this->dV;
    if(velocity.ModuleQuadr() > this->max_speed * max_speed)
    {
        velocity = velocity * 0.96;
    }

    if(Abs_vect_to_player < 10)
    {
        velocity = -max_speed/Abs_vect_to_player * vect_to_player;
        
    }
    
    if( this->dV.x * this->dV.x >= this->dV.y * this->dV.y && this->dV.x <= 0) // т.е. он идет влево
    {
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed*150)/10000)%10 + 10 ];
        HeadSprite.setTextureRect(sf::IntRect(96,0,-32,32));
        BodySprite.scale(-1,1);
        BodyDirection = "Left";
    }
    else if(this->dV.x * this->dV.x >= this->dV.y * this->dV.y && this->dV.x >= 0) // т.е. он идет вправо
    {
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed * 150)/10000)%10 + 10 ];
        HeadSprite.setTextureRect(sf::IntRect(64,0,32,32));    
        BodyDirection = "Right";
    }
    else if(this->dV.x * this->dV.x <= this->dV.y * this->dV.y && this->dV.y >= 0) // т.е. он идет вниз
    {
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed*150)/10000)%10 ];
        HeadSprite.setTextureRect(sf::IntRect(0,0,32,32));
        BodyDirection = "Down";
    }
    else if(this->dV.x * this->dV.x <= this->dV.y * this->dV.y && this->dV.y <= 0)// т.е. он идет вверх
    {
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed*150)/10000)%10 ];
        HeadSprite.setTextureRect(sf::IntRect(128,0,32,32));
        BodyDirection = "Up";
    }

    this->coord = this->coord + this->velocity * time;
    this->HeadSprite.setPosition({this->coord.x - 16, this->coord.y - 32} );
    if(this->BodyDirection != "Left") this->BodySprite.setPosition({this->coord.x - 16, this->coord.y + 20 - 32} ); // -16 и -32 чтобы спрайт рисовался не в угле а в центре
    if(this->BodyDirection == "Left") this->BodySprite.setPosition({this->coord.x - 16 + 64, this->coord.y + 20 - 32} ); // +64 и +20 - чтобы тело и голова были связаны
}


int Zombie::turn(Player& pl, list<Zombie>& Zombies)
{
    if(this->getHealth() <= 0)
    {
        return 0; // зомби умер
    }
    else
    {
        MoveInertion(pl);
        for(auto it = Zombies.begin(); it != Zombies.end(); it++)
        {
            if ( (this->coord - it->coord).ModuleQuadr() < 1000)
            {
                Vector2D deltaV = -acceleration/(this->coord - it->coord).Module() * (this->coord - it->coord);
                it->velocity = it->velocity + 5*(this->mass/it->mass) * dV; // эффект должен быть в 2 раза меньше т.к. взаимодействие учитывается 2 раза
                this->velocity = this->velocity - 5*(it->mass/this->mass) * dV;
            }
        }
        if ( (this->coord - pl.coord).ModuleQuadr() < 1000)
        {
            pl.velocity = pl.velocity + (5 * this->mass/pl.mass) * dV;
            this->velocity = this->velocity - (2 * pl.mass/this->mass) * dV;
            pl.getDamage(1);
        }

        return 1;
    }

}

void Zombie::getDamage(Tear &t)
{
    this->health -= t.Damage;
    this->velocity = this->velocity + t.mass/this->mass * t.velocity;
    cout << this->name << " got " << t.Damage << " damage\n";

}

void Zombie::death()
{
    cout << "Player is dead" << endl;
}