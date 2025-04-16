#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include <chrono>
#include <thread>
#include <list>


using std::list;

int main()
{
    
    list<Tear> Tears(0);
    list<Zombie> Zombies;

    bool EnableInertion = 1;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "The Binding of the Isaac"); // с этой частью связана утечка приемрно в 259,467 байт
    int delta_time = 5;

    Player Isaac(1, 0.8 * delta_time, 5);

    sf::Texture Z1_texture;
    Z1_texture.loadFromFile("Textures/Zombie.png");

    Zombie Z1(6, 0.2 * delta_time, Z1_texture);
    Zombies.push_back(Z1);

    while (window.isOpen())
    {

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
            int WhatHappened = it_Monst->turn(Isaac);
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


        Isaac.turn(event, EnableInertion, Tears);


        auto it_Tear = Tears.begin();
        while(it_Tear != Tears.end()) // ход слез
        {
            it_Tear->sprite.setTexture(it_Tear->texture); // почему у слез не установлен спрайт по умолчанию?
            int WhatHappened = it_Tear->turn(Zombies);
            if (WhatHappened == 1) // т.е. если слеза не врезаласась
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
        }


        window.clear(); // пошла отрисовка
        for(auto it = Tears.begin(); it != Tears.end(); ++it)
        {
            window.draw(it->getSprite());
        }
        for(auto it = Zombies.begin(); it != Zombies.end(); ++it)
        {
            window.draw(it->getSprite());
        }

        
        window.draw(Isaac.BodySprite);
        window.draw(Isaac.HeadSprite);
        window.display();
        
    }
    return 0;
}