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
    
    list<Tear> Tears;
    list<Entity> Monsters;

    bool EnableInertion = 1;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "The Binding of the Isaac"); // с этой частью связана утечка приемрно в 259,467 байт
    int delta_time = 5;

    sf::Texture Isaac_texture;
    Isaac_texture.loadFromFile("Textures/Isaac.png");
    Player Isaac(1, 0.8 * delta_time, Isaac_texture);

    sf::Texture Z1_texture;
    Z1_texture.loadFromFile("Textures/Zombie.png");

    Zombie Z1(1, 0.2 * delta_time, Z1_texture);
    Monsters.push_back(Z1);

    while (window.isOpen())
    {

        std::this_thread::sleep_for(std::chrono::milliseconds(delta_time));
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            
        }

        Z1.turn(Isaac);
                                                                    cout << Z1.getCoord() << endl;
        cout << "Monsters.begin()->getCoord() = " << Monsters.begin()->getCoord() << endl;
        Isaac.turn(event, EnableInertion, Tears);
        for(auto it = Tears.begin(); it != Tears.end(); ++it)
        {
            it->sprite.setTexture(it->texture); // почему у слез не установлен спрайт по умолчанию?
            int WhatHappened = it->turn(Monsters);

            if (WhatHappened == 1) // т.е. если слеза не врезаласась
            {
                continue;
            }
            if (WhatHappened == 0) // т.е. слеза врезалась (в монстра)
            {
                Tears.erase(it);
                cout << "Get in Moster and disappeared\n";
                //if(Tears.empty()) break;
                break;
            } 
            
        } 
        window.clear();


        for(auto it = Tears.begin(); it != Tears.end(); ++it)
        {
            window.draw(it->getSprite());
        }
        window.draw(Isaac.getSprite());
        window.draw( Z1.getSprite() );
        window.display();

        //cout << timer << endl;
        
    }
    cout << "nothing\n";
    return 0;
}