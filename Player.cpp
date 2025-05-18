#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "GlobalVariables.hpp"

Room* FindRmMaxim(int id, std::vector<Room*> rooms){
    Room* pr;
    for(auto& x : rooms){
        int s = x->getRoomId();
        if(s == id){
            pr = x;
        }
    }
    return pr;
};

Player::Player(int hp, float max_speed, float Damage, float TearsFreq, float Range, float ShotSpeed, float Luck, float TearMass)
{
    SizeX = 24;
    SizeY = 24;
    this->heatbox.width = SizeX * 1.1;
    this->heatbox.height = SizeY * 1.4;
    

    GettingItemTexture.loadFromFile("Textures/IsaacTexture3.png");
    this->GettingItemSprite.setTexture(GettingItemTexture); 
    GettingItemSprite.scale(SizeX/40, SizeY/40);

    this->GettingDamageSprite.setTexture(GettingItemTexture); //не опечатка ибо в GettingItemTexture лежит целиком текстура со всеми "эмоциями Айзека"
    GettingDamageSprite.scale(SizeX/40, SizeY/40);
    GettingItem = 0;

    this->health = hp;
    this->HPContCount = hp;

    this->max_speed = max_speed;
    this->Damage = Damage;
    this->TearsFreq = TearsFreq; // скорострельность
    this->Range = Range;
    this->ShotSpeed = ShotSpeed;
    this->Luck = Luck;
    

    HealthConteinersTexture.loadFromFile("Textures/HealthConteiner.png");
    HealthHeartsTexture.loadFromFile("Textures/Health.png");

    for(int i = 0; i < 12; i++)
    {
        sf::Sprite HPContSprite(HealthConteinersTexture); // спрайты контйенеров
        HPContSprite.setPosition(20 + i * 45, 20);
        HPContSprite.scale(0.8, 0.8);
        HealthConteiners.push_back(HPContSprite);
    }

    for(int i = 0; i < 12; i++)
    {
        sf::Sprite HPSprite(HealthHeartsTexture);
        HPSprite.setPosition(3620 + i * 45, 3620); 
        HPSprite.scale(0.8, 0.8);
        HealthHearts.push_back(HPSprite);
    }

    this->coord = {350,300};

    /*font.loadFromFile("Fonts/TimesNewRoman.ttf");
    this->max_speed_Text.setFont(font);
    this->DamageText.setFont(font);
    this->TearsFreqText.setFont(font);

    this->max_speed_Text.setPosition(20, 100); this->max_speed_Text.setString(std::to_string(this->max_speed)); max_speed_Text.setFillColor(sf::Color::Green);
    */ // проклято - почему то вызывает segmentation fault при отрисовке max_speed_Text
    this->CharacteristicsTexture.loadFromFile("Textures/Characteristics.png");
    this->CharacteristicsSprite.setTexture(this->CharacteristicsTexture);
    this->CharacteristicsSprite.setPosition(3600, 3700);
    this->CharacteristicsSprite.scale(0.8,0.8);


    this->TearMass = TearMass;
    this->mass = 3;

    BodyDirection = "Down";
    HeadDirection = "Down";
    this->time_invicibility = 1;
    this->name = "Isaac";
    this->acceleration = max_speed/5;

    this->texture.loadFromFile("Textures/Isaac_textures.png");
    this->HeadSprite.setTexture(this->texture);
    this->HeadSprite.setTextureRect(sf::IntRect(0,0,32,32));
    this->HeadSprite.setScale(SizeX/20,SizeY/20);
    
    this->BodySprite.setTexture(this->texture);
    this->BodySprite.setTextureRect(sf::IntRect(0,32,32,32));
    //this->BodySprite.setScale(2,2);

    sf::Sprite temp; 
    temp.setTexture(this->texture);
    this->coord.x += 3600; 
    this->coord.y += 3600; 
    temp.setPosition(this->coord.x, this->coord.y);
    temp.scale(SizeX/20,SizeY/20); 

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

void Player::MoveInertion(sf::Event event, vector<Room*>& rooms, float time) // что просходит с игроком в каждом кадре
{
    for(auto spr : this->BodyAnimationSprites) spr.setPosition(this->coord.x + 3600, this->coord.y + 3600); // спрайты анимации "ходят за Айзеком"

    //cout << "Player's turn" << endl;
    Vector2D dV = {0,0};
    Vector2D null_vect = {0,0};

    float time_from_shooting = (float)this->tears_time.getElapsedTime().asMilliseconds()/1000;
    int BodyAnimationTime = (float)this->body_time.getElapsedTime().asMicroseconds()/1000;


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
        BodyDirection = "Right";                                                                                // существует баг, что если быстро нажимать W-A-S-D
        BodySprite = BodyAnimationSprites[ (BodyAnimationTime * int(this->max_speed * 100)/30000)%10 + 10 ];    // то появляется спрайт тела в (0,0) - это связано с тем что программа считает, 
        if(time_from_shooting > 0.5)                                                                            //что за 1 кадр (по умолчанию 10 мс) нажатые на клавиатуре клавиши не успевают измениться
        {                                                                                                       // исправляется заменой всех sf::keyboard::isPressed на event.type == keypressed...
            HeadSprite.setTextureRect(sf::IntRect(64,0,32,32));                                                 // т.е. в течение 1 кадра event = const
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


    if (dV.x == 0) velocity.x = velocity.x * 0.8; // т.е. в случае если мы ничего не нажимаем (персонаж должен сам затормозить)
    if (dV.y == 0) velocity.y = velocity.y * 0.8; // коэфициент подобран опытным путем
    
    if(dV == null_vect) this->body_time.restart(); // пока Айзек не ходит - таймер анимации на нуле

    this->velocity = this->velocity + dV;
    if (velocity.ModuleQuadr() > max_speed * max_speed) // если скорость стала больше максимальной, ее надо уменьшить
    {
        float k_decr = max_speed/( sqrt( velocity.ModuleQuadr() ) ); // самый "долгий момент" - счет корня
        velocity = velocity * k_decr;
    }
    
    Room* RoomPointer = FindRmMaxim(this->roomId, rooms);

    this->coord.x = this->coord.x + this->velocity.x * time;
    this->heatbox.left = this->coord.x - (int)(SizeX * 0.5);
    
    int trig = 0;

    for( auto& ObjectPointer : RoomPointer->getObj() )
    {
        if( ObjectPointer->getName() == "solid" )
        {
            if( this->heatbox.intersects(ObjectPointer->getRect()))
            {
                this->coord.x = this->coord.x - this->velocity.x * time;
                this->velocity.x = 0;
                this->heatbox.left = this->coord.x - (int)(SizeX * 0.5);
                trig = 1;
                break;
            }
        }
    }


    this->coord.y = this->coord.y + this->velocity.y * time;
    this->heatbox.top = this->coord.y - (int)(SizeY * 0.5);

    trig = 0;

    for( auto& ObjectPointer : RoomPointer->getObj() )
    {
        if( ObjectPointer->getName() == "solid" )
        {
            if( this->heatbox.intersects(ObjectPointer->getRect()) ) // 600х600 это пока что костыль
            {
                this->coord.y = this->coord.y - this->velocity.y * time;
                this->velocity.y = 0;
                this->heatbox.top = this->coord.y - (int)(SizeY * 0.5);
                trig = 1;
                break;
            }
        }
    } 


    this->HeadSprite.setPosition({this->coord.x - (int)(SizeX * 0.7), this->coord.y - int(SizeY * 1)} );
    if(BodyDirection != "Left") this->BodySprite.setPosition({this->coord.x - (int)(SizeX * 0.7), this->coord.y - int(SizeY * 0.5)} ); 
    if(BodyDirection == "Left") this->BodySprite.setPosition({this->coord.x + (int)(SizeX * 1), this->coord.y - int(SizeY * 0.5)} ); 
    
    // cout << "heatbox : " << heatbox.getPosition().x << " " << heatbox.getPosition().y << endl; // отладочный вывод хитбокса
    return;

}



void Player::shoot(sf::Event event, list<Tear>& Tears)
{
    float time_from_shooting = (float)this->tears_time.getElapsedTime().asMilliseconds()/1000;
    
    if(time_from_shooting > 1/(3*this->TearsFreq) )
    {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {HeadSprite.setTextureRect(sf::IntRect(96,0,-32,32)); HeadDirection = "Left";} // возвращение головы несжатое состояние
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {HeadSprite.setTextureRect(sf::IntRect(64,0,32,32)); HeadDirection = "Right";}
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {HeadSprite.setTextureRect(sf::IntRect(0,0,32,32)); HeadDirection = "Down";}
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {HeadSprite.setTextureRect(sf::IntRect(128,0,32,32)); HeadDirection = "Up";}
    }



    if (time_from_shooting > 1/this->TearsFreq )
    {

        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {HeadSprite.setTextureRect(sf::IntRect(128,0,-32,32)); HeadDirection = "Left";} // сейчас сделан выстрел
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {HeadSprite.setTextureRect(sf::IntRect(96,0,32,32)); HeadDirection = "Right";} // анимация где голова чуток уменьшается
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {HeadSprite.setTextureRect(sf::IntRect(32,0,32,32)); HeadDirection = "Down";}
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {HeadSprite.setTextureRect(sf::IntRect(160,0,32,32)); HeadDirection = "Up";}
        
        this->tears_time.restart();
        Tear T(*this, event); // тут у слезы есть спрайт, но при переносе в Tears он пропадает
        Tears.push_back(T); // пока что в main.cpp стоит костыль 
    }

} 

void Player::turn(sf::Event event, bool EnableInertion, list<Tear>& Tears, vector<Room*>& rooms, float time)
{   
    float time_from_shooting = (float)this->tears_time.getElapsedTime().asMilliseconds()/1000;
    float time_from_damage = (float)this->damage_time.getElapsedTime().asMilliseconds()/1000;

    this->BodySprite = this->BodyAnimationSprites[2];
    this->BodySprite.setPosition({this->coord.x - 16, this->coord.y + 20 - 32} ); 
    

    if(time_from_shooting > 1/(3*this->TearsFreq) )
    {
        if( HeadDirection == "Left") HeadSprite.setTextureRect(sf::IntRect(96,0,-32,32)); // возвращение головы в несжатое состояние
        if( HeadDirection == "Right") HeadSprite.setTextureRect(sf::IntRect(64,0,32,32));
        if( HeadDirection == "Down") HeadSprite.setTextureRect(sf::IntRect(0,0,32,32));
        if( HeadDirection == "Up") HeadSprite.setTextureRect(sf::IntRect(128,0,32,32));
    } 

    if(time_from_shooting > 0.8) HeadSprite.setTextureRect(sf::IntRect(0,0,32,32)); // если ничего не происходит (кнопки не нажаты), то Айзек смотрит вниз


    //HeadDirection = "Down";
    BodyDirection = "Down";

    MoveInertion(event, rooms, time);

    //if (event.type == sf::Event::KeyPressed)
    //{
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        {
            shoot(event, Tears);
            //cout << "Shoot\n";    
        } 
        //cout << "event.type == sf::Event::KeyPressed\n";
        
        
    //} 
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) cout << "sf::Keyboard::isKeyPressed(sf::Keyboard::Left)\n";

    if(this->GettingItem) // 160 432 64 64
    {
        float time = GettingItemTime.getElapsedTime().asMilliseconds();
        if( time > 1500)
        {
            GettingItem = 0;
        }
        
        this->GettingItemSprite.setTextureRect(sf::IntRect(160, 432, 64, 64) ); // подбор предмета
        this->GettingItemSprite.setPosition(this->coord.x - (int)(SizeX * 0.6), this->coord.y - (int)(SizeY * 1));
    }


    if( time_from_damage < this->time_invicibility)
    {
        this->GettingDamageSprite.setTextureRect(sf::IntRect(288, 430, 64, 64) ); // получение урона
        this->GettingDamageSprite.setPosition(this->coord.x - (int)(SizeX * 0.6), this->coord.y - (int)(SizeY * 1));
    }
}

void Player::death()
{
    cout << "Player is dead" << endl;
}

void Player::getDamage(int D)
{
    float time_from_damage = (float)this->damage_time.getElapsedTime().asMilliseconds()/1000;
    if (time_from_damage > this->time_invicibility)
    {
        this->damage_time.restart();
        this->health -= D;
        cout << this->name << " got " << D << " damage" << endl;
        cout << this->name << "'s health = " << this->health << endl;
        if(not this->HealthHearts.empty() )
            this->HealthHearts.pop_back();
    }
}

void Player::draw(sf::RenderWindow &window)
{
    int time_from_damage = this->damage_time.getElapsedTime().asMilliseconds();
    auto it_HPCont = HealthConteiners.begin();
    for(int i = 0; i < this->HPContCount; i++)
    {
        window.draw(*it_HPCont); // отрисовка контейнеров хп
        it_HPCont++;
    }

    auto it_HPHearts = HealthHearts.begin();
    for(int i = 0; i < this->health; i++)
    {
        window.draw(*it_HPHearts); // отрисовка хп
        it_HPHearts++;
    }

    if( time_from_damage < time_invicibility * 1000)
    {
        if(time_from_damage%200 < 100) window.draw(this->GettingDamageSprite);
        else {};
    }
    else // первостепенно в анимации - получение урона
    {
        if(not GettingItem)
        {
            window.draw(this->BodySprite);
            window.draw(this->HeadSprite);
        }
        else
        {
            window.draw(this->GettingItemSprite);
        }
    }

    window.draw(this->CharacteristicsSprite);

    /*   // отладочное отображение центра персонажа
    sf::Texture CenterTexture;
    CenterTexture.loadFromFile("Textures/Bomb.png");
    sf::Sprite CenterSprite;
    CenterSprite.setTexture(CenterTexture);
    CenterSprite.setPosition(coord.x, coord.y);
    CenterSprite.scale(0.1, 0.1);
    window.draw(CenterSprite);
    */
}
