#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

Player::Player(int hp, float max_speed, float range)
{
    this->range = range;

    BodyDirection = "Down";
    HeadDirection = "Down";
    this->time_betweenshoots = 0.5;
    this->time_invicibility = 1;
    this->name = "Isaac";
    this->acceleration = max_speed/20;
    this->health = hp;
    this->max_speed = max_speed;
    this->texture.loadFromFile("Textures/Isaac_textures.png");
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



void Player::MoveInertion(sf::Event event) // что просходит с игроком в каждом кадре
{
    for(auto spr : this->BodyAnimationSprites) spr.setPosition(this->coord.x, this->coord.y); // спрайты анимации "ходят за Айзеком"

    float time = 1;
    //cout << "Player's turn" << endl;
    Vector2D dV = {0,0};
    Vector2D null_vect = {0,0};

    float time_from_shooting = this->tears_time.getElapsedTime().asSeconds();
    int BodyAnimationTime = this->body_time.getElapsedTime().asMilliseconds();


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
    {
        dV.x -= acceleration * time; // нажимая на кнопки мы контролируем не скорость, а ускорение чтобы была инерция
        BodyDirection = "Left";
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed*100)/30000)%10 + 10 ];
        BodySprite.scale(-1,1);
        if(time_from_shooting > 0.5)  
        {
            HeadSprite.setTextureRect(sf::IntRect(96,0,-32,32));
            HeadDirection = "Left";
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
    {
        dV.x += acceleration * time;
        BodyDirection = "Right";                                                                    // существует баг, что если быстро нажимать W-A-S-D
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed * 100)/30000)%10 + 10 ];     // то появляется спрайт тела в (0,0) - это связано с тем что программа считает, 
        if(time_from_shooting > 0.5)                                                                //что за 1 кадр (по умолчанию 10 мс) нажатые на клавиатуре клавиши не успевают измениться
        {                                                                                           // исправляется заменой всех sf::keyboard::isPressed на event.type == keypressed...
            HeadSprite.setTextureRect(sf::IntRect(64,0,32,32));                                     // т.е. в течение 1 кадра event = const
            HeadDirection = "Right";                                      
        }                                                                          
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
    {
        dV.y += acceleration * time;
        BodyDirection = "Down";
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed*100)/30000)%10 ];
        if(time_from_shooting > 0.5)
        {
            HeadSprite.setTextureRect(sf::IntRect(0,0,32,32));
            HeadDirection = "Down";
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
    {
        dV.y -= acceleration * time;
        BodyDirection = "Up";
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed*100)/30000)%10 ];
        if(time_from_shooting > 0.5)
        {
            HeadSprite.setTextureRect(sf::IntRect(128,0,32,32));
            HeadDirection = "Up";
        }
    }

    if (dV.ModuleQuadr() > (acceleration * time) * (acceleration * time) ) 
    {
        dV = dV * 0.7071067; // нормировка чтобы по модулю dV было равно ускорению * коэф
    }


    if (dV == null_vect) // т.е. в случае если мы ничего не нажимаем (персонаж должен сам затормозить)
    {
        this->body_time.restart(); // пока Айзек не ходит - таймер анимации на нуле
        if (velocity.ModuleQuadr() < (max_speed/10)*(max_speed/10))
        {
            velocity = {0,0};
            return;
        }
        else
        {
            velocity = velocity * 0.94; // коэфициент подобран опытным путем
        }
    }

    this->velocity = this->velocity + dV;
    if (velocity.ModuleQuadr() > max_speed * max_speed) // если скорость стала больше максимальной, ее надо уменьшить
    {
        float k_decr = max_speed/( sqrt( velocity.ModuleQuadr() ) ); // самый "долгий момент" - счет корня
        velocity = velocity * k_decr;
    }
    
    this->coord = this->coord + this->velocity * time;


    this->HeadSprite.setPosition({this->coord.x, this->coord.y} );
    if(BodyDirection != "Left") this->BodySprite.setPosition({this->coord.x, this->coord.y + 20} );
    if(BodyDirection == "Left") this->BodySprite.setPosition({this->coord.x + 64, this->coord.y + 20} );
    
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

    this->HeadSprite.setPosition({this->coord.x, this->coord.y} );
    this->BodySprite.setPosition({this->coord.x, this->coord.y + 20} );
}

void Player::shoot(sf::Event event, list<Tear>& Tears)
{
    float time_from_shooting = this->tears_time.getElapsedTime().asSeconds();
    
    if(time_from_shooting > this->time_betweenshoots/3)
    {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {HeadSprite.setTextureRect(sf::IntRect(96,0,-32,32)); HeadDirection = "Left";} // возвращение головы несжатое состояние
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {HeadSprite.setTextureRect(sf::IntRect(64,0,32,32)); HeadDirection = "Right";}
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {HeadSprite.setTextureRect(sf::IntRect(0,0,32,32)); HeadDirection = "Down";}
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {HeadSprite.setTextureRect(sf::IntRect(128,0,32,32)); HeadDirection = "Up";}
    }



    if (time_from_shooting > this->time_betweenshoots)
    {

        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {HeadSprite.setTextureRect(sf::IntRect(128,0,-32,32)); HeadDirection = "Left";} // сейчас сделан выстрел
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {HeadSprite.setTextureRect(sf::IntRect(96,0,32,32)); HeadDirection = "Right";} // анимация где голова чуток уменьшается
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {HeadSprite.setTextureRect(sf::IntRect(32,0,32,32)); HeadDirection = "Down";}
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {HeadSprite.setTextureRect(sf::IntRect(160,0,32,32)); HeadDirection = "Up";}

        this->tears_time.restart();
        Tear T(this->coord, event, this->range, this->HeadDirection); // тут у слезы есть спрайт, но при переносе в Tears он пропадает
        Tears.push_back(T); // пока что в main.cpp стоит костыль 
    }

} 

void Player::turn(sf::Event event, bool EnableInertion, list<Tear>& Tears)
{

    
    
        
    
    float time_from_shooting = this->tears_time.getElapsedTime().asSeconds();


    this->BodySprite = this->BodyAnimationSprites[2];
    this->BodySprite.setPosition({this->coord.x, this->coord.y + 20} );

    if(time_from_shooting > this->time_betweenshoots/3)
    {
        if( HeadDirection == "Left") HeadSprite.setTextureRect(sf::IntRect(96,0,-32,32)); // возвращение головы в несжатое состояние
        if( HeadDirection == "Right") HeadSprite.setTextureRect(sf::IntRect(64,0,32,32));
        if( HeadDirection == "Down") HeadSprite.setTextureRect(sf::IntRect(0,0,32,32));
        if( HeadDirection == "Up") HeadSprite.setTextureRect(sf::IntRect(128,0,32,32));
    } 

    if(time_from_shooting > 0.8) HeadSprite.setTextureRect(sf::IntRect(0,0,32,32)); // если ничего не происходит (кнопки не нажаты), то Айзек смотрит вниз


    //HeadDirection = "Down";
    BodyDirection = "Down";

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
    float time = this->damage_time.getElapsedTime().asSeconds();
    if (time > this->time_invicibility)
    {
        this->damage_time.restart();
        this->health -= D;
        cout << this->name << " got " << D << " damage" << endl;
        cout << this->name << "'s health = " << this->health << endl;
    }
}
