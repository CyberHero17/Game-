#include <iostream>
#include <chrono>
#include <thread>
#include <list>

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
//#include "Player.cpp" 
#include "Zombie.hpp"
#include "GlobalVariables.hpp"
#include "Breakfast.hpp"
#include "Creator.hpp"
#include "View.hpp"


using std::list;

int main()
{
    HealthHeartsTexture.loadFromFile("Textures/Health.png");
    GettingItemTexture.loadFromFile("Textures/IsaacTexture3.png");
    
    list<Tear> Tears;
    list<Zombie> Zombies;

    bool EnableInertion = 1;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "The Pinging of the Isaac"); // с этой частью связана утечка приемрно в 259,467 байт
    int delta_time = 5;

    Player Isaac(5, 0.8 * delta_time, 2, 3 , 5.0f, 5, 0, 2);

    Zombie Z1(6, 0.2 * delta_time, {3700,3800}); Zombies.push_back(Z1);
    Zombie Z2(6, 0.2 * delta_time, {3750,3800}); Zombies.push_back(Z2);
    Zombie Z3(6, 0.2 * delta_time, {3800,3800}); Zombies.push_back(Z3);
    Zombie Z4(6, 0.2 * delta_time, {3700,3800}); Zombies.push_back(Z4);
    
    Breakfast Br ({4000,3900});
    // r1.CreateObjects();
    // r1.CreateRoom(ptr, x, y);

    Fill(vm);
    PlaceRooms(vm, X0, Y0);
    makeNumOfRooms(vm);
    Place(vm);
    ConnectRm(vm);

    //Door d1(std::move("Textures/Door.png"));
    // for(auto& r : rooms){
    //     r->PlaceDoors();
    // }


    while (window.isOpen())
    {
        //sf:Clock WorldClock;
        std::this_thread::sleep_for(std::chrono::milliseconds(delta_time));
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            
        }
        auto it_Monst = Zombies.begin();
        while(it_Monst != Zombies.end())
        {
            int WhatHappened = it_Monst->turn(Isaac, Zombies);
            if (WhatHappened == 1) // т.е. если с монстром ничего не произошло
            {    
                it_Monst++;
                continue;
            }

            if (WhatHappened == 0) // т.е. зомби умер
            {
                it_Monst = Zombies.erase(it_Monst);
                continue;
            }

        }

        Br.turn(Isaac);
        Isaac.turn(event, EnableInertion, Tears);
        

        auto it_Tear = Tears.begin();
        while(it_Tear != Tears.end()) // ход слез
        {
            it_Tear->sprite.setTexture(it_Tear->texture); // почему у слез не установлен спрайт по умолчанию?
            int WhatHappened = it_Tear->turn(Zombies);
            if (WhatHappened == 1) // т.е. если слеза не врезаласась или уже уничтожена и просто проигрывает свою анимацию
            {
                it_Tear++;
                continue;
            }
            if (WhatHappened == 0) // т.е. слеза врезалась (в монстра)
            {
                it_Tear = Tears.erase(it_Tear); // переместить итератор на следующий
                continue;
            } 
            if(WhatHappened == 2) // т.е. слеза изжила свое время
            {
                it_Tear = Tears.erase(it_Tear); // да, набор действий такой же как и при попадании в монстра, но пока оставим так, вдруг потом изменится
                continue;
            }
            if(WhatHappened == 3) // т.е. надо запустить анимацию
            {
                it_Tear++;
                continue;
            }
        }


        window.clear(); // пошла отрисовка
        //r1.Draw(window);
        
        for(auto& x : rooms){
            x->Draw(window);
            if(x->getRoomId() == Isaac.roomId[0]) x->Teleport(Isaac);
        } 

        window.setView(getCordsForView(Isaac.coord.x, Isaac.coord.y));


        for(auto it = Zombies.begin(); it != Zombies.end(); ++it)
        {
            window.draw(it->BodySprite);
            window.draw(it->HeadSprite);
        }

        
        Br.draw(window);
        
        for(auto it = Tears.begin(); it != Tears.end(); ++it)
        {
            window.draw(it->getSprite());
        }

        Isaac.draw(window);
        //-----------
        Isaac.CharacteristicsSprite.setPosition(Isaac.coord.x - 360.0f, Isaac.coord.y - 220.0f);    // движение характеристик
        int step = 0;
        for(auto& it : Isaac.HealthConteiners){
            it.setPosition(Isaac.coord.x - 300.0f + step * 45, Isaac.coord.y - 220.0f);
            step++;
        }
        step = 0;
        for(auto& it : Isaac.HealthHearts){
            it.setPosition(Isaac.coord.x - 300.0f + step * 45, Isaac.coord.y - 220.0f);
            step++;
        }
        //window.draw(Isaac.max_speed_Text); // SgFault
        

        window.display();
        
    }
    rooms.clear();
    return 0;
}