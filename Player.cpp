#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

Player::Player(int hp, float max_speed, sf::Texture texture)
{
    this->acceleration = max_speed * 4;
    this->health = hp;
    this->max_speed = max_speed;
    this->texture = texture;
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.75, 0.75);
}

Player::Player()
{
    this->acceleration = 8;
    this->health = 10;
    this->max_speed = 2;
    this->texture.loadFromFile("Textures/Isaac.png");
    this->sprite.setTexture(this->texture);
    //this->sprite.setScale(0.5, 0.5);
    this->coord = {500, 200};
}

void Player::MoveInertion(sf::Event event) // что просходит с игроком в каждом кадре
{
    float koef = 0.01;
    //cout << "Player's turn" << endl;
    Vector2D dV;
    dV.x = -velocity.x/max_speed * acceleration * koef;
    dV.y = -velocity.y/max_speed * acceleration * koef;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dV.x -= acceleration * koef; // нажимая на кнопки мы контролируем не скорость, а ускорение чтобы была инерция
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dV.x += acceleration * koef;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dV.y += acceleration * koef;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dV.y -= acceleration * koef;

    if (dV.x * dV.x + dV.y * dV.y > (acceleration * koef) * (acceleration * koef) ) 
    {
        dV.x = dV.x * 0.7071067; // нормировка чтобы по модулю dV было равно ускорению * коэф
        dV.y = dV.y * 0.7071067;
    }
    //cout << "dV =" << dV.x << " " << dV.y << endl;

    this->velocity.x = this->velocity.x + dV.x;
    this->velocity.y = this->velocity.y + dV.y;
    //cout << "V =" << velocity.x << " " << velocity.y << endl;
    if (velocity.x * velocity.x + velocity.y * velocity.y > max_speed * max_speed) // если скорость стала больше максимальной, ее надо уменьшить
    {
        float k_decr = max_speed/( sqrt( velocity.x * velocity.x + velocity.y * velocity.y ) ); // самый "долгий момент" - счет корня
        velocity.x = velocity.x * k_decr;
        velocity.y = velocity.y * k_decr;
    }

    this->coord.x = this->coord.x + this->velocity.x;
    this->coord.y = this->coord.y + this->velocity.y;
    
    this->sprite.setPosition({this->coord.x, this->coord.y} );
}

void Player::MoveWithoutIntertion(sf::Event event)
{
    float koef = 1;
    //cout << "Player's turn" << endl;
    Vector2D dr = {0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dr.x -= max_speed * koef; // нажимая на кнопки мы контролируем не скорость, а ускорение чтобы была инерция
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dr.x += max_speed * koef;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dr.y += max_speed * koef;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dr.y -= max_speed * koef;

    if (dr.x * dr.x + dr.y * dr.y > (max_speed * koef) * (max_speed * koef) ) 
    {
        dr.x = dr.x * 0.7071067; // нормировка чтобы по модулю dX было равно V * коэф
        dr.y = dr.y * 0.7071067;
    }

    this->coord.x += dr.x;
    this->coord.y += dr.y;

    this->sprite.setPosition({this->coord.x, this->coord.y});
}

void Player::turn(sf::Event event, bool EnableInertion)
{
    if(EnableInertion) MoveInertion(event);
    else MoveWithoutIntertion(event);
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
