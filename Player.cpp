#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

Player::Player(int hp, float max_speed, sf::Texture texture)
{
    this->acceleration = max_speed/20;
    this->health = hp;
    this->max_speed = max_speed;
    this->texture = texture;
    this->sprite.setTexture(this->texture);
}

Player::Player()
{
    this->acceleration = 8;
    this->health = 10;
    this->max_speed = 2;
    this->texture.loadFromFile("Textures/Isaac.png");
    this->sprite.setTexture(this->texture);
    this->coord = {500, 200};
}

void Player::MoveInertion(sf::Event event) // что просходит с игроком в каждом кадре
{
    float time = 1;
    //cout << "Player's turn" << endl;
    Vector2D dV = {0,0};
    Vector2D null_vect = {0,0};



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dV.x -= acceleration * time; // нажимая на кнопки мы контролируем не скорость, а ускорение чтобы была инерция
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dV.x += acceleration * time;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dV.y += acceleration * time;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dV.y -= acceleration * time;

    if (dV.ModuleQuadr() > (acceleration * time) * (acceleration * time) ) 
    {
        dV = dV * 0.7071067; // нормировка чтобы по модулю dV было равно ускорению * коэф
    }
    //cout << "dV =" << dV.x << " " << dV.y << endl;


    if (dV == null_vect) // т.е. в случае если мы ничего не нажимаем (персонаж должен сам затормозить)
    {
        if (velocity.ModuleQuadr() < (max_speed/10)*(max_speed/10))
        {
            velocity = {0,0};
            return;
        }
        else
        {
            velocity = velocity * 0.94;
        }
    }

    this->velocity = this->velocity + dV;
    //cout << "V =" << velocity.x << " " << velocity.y << endl;
    if (velocity.ModuleQuadr() > max_speed * max_speed) // если скорость стала больше максимальной, ее надо уменьшить
    {
        float k_decr = max_speed/( sqrt( velocity.ModuleQuadr() ) ); // самый "долгий момент" - счет корня
        velocity = velocity * k_decr;
    }
    
    this->coord = this->coord + this->velocity * time;
    this->sprite.setPosition({this->coord.x, this->coord.y} );
    return;

}

void Player::MoveWithoutIntertion(sf::Event event)
{
    //cout << "Player's turn" << endl;
    float time = 1;
    Vector2D dr = {0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dr.x -= max_speed * time; // нажимая на кнопки мы контролируем не скорость, а ускорение чтобы была инерция
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dr.x += max_speed * time;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dr.y += max_speed * time;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dr.y -= max_speed * time;

    if (dr.x * dr.x + dr.y * dr.y > (max_speed * time) * (max_speed * time) ) 
    {
        dr.x = dr.x * 0.7071067; // нормировка чтобы по модулю dX было равно V * коэф
        dr.y = dr.y * 0.7071067;
    }
    

    this->coord.x += dr.x;
    this->coord.y += dr.y;

    this->sprite.setPosition({this->coord.x, this->coord.y} );
}

void Player::shoot(sf::Event event, list<Tear>& Tears)
{
    float time = this->clock.getElapsedTime().asSeconds();
    
    if (time > 0.5)
    {
        this->clock.restart();
        Tear T(this->coord, event); // тут у слезы есть спрайт, но при переносе в Tears он пропадает
        Tears.push_back(T); // пока что в main.cpp стоит костыль 
    }

} 

void Player::turn(sf::Event event, bool EnableInertion, list<Tear>& Tears)
{

    if(EnableInertion) MoveInertion(event);
    else MoveWithoutIntertion(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        {
            shoot(event, Tears);
        } 
    } 
}

void Player::death()
{
    cout << "Player is dead" << endl;
}

void Player::getDamage(int D)
{
    health -= D;
    cout << "Got " << D << " damage\n";
}







