#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
//#include "map.hpp"
#include "View.hpp"
int main()
{
    bool EnableInertion = 1;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "The Binding of the Isaac");

    sf::Texture Isaac_texture;
    Isaac_texture.loadFromFile("Textures/Isaac.png");
    Player Isaac(1, 2, Isaac_texture);

    sf::Texture Z1_texture;
    Z1_texture.loadFromFile("Textures/Zombie.png");
    Zombie Z1(1, 1, Z1_texture);

    // r1.LoadTextureFromFile("Textures/basement.png");
    // r1.setSpriteTexture();
    
    r1.CreateRoom(Id, ptr, x, y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Z1.turn(Isaac);
        Isaac.turn(event, EnableInertion);

        window.clear();
        r1.Draw(window);
        
        window.draw( Z1.getSprite() );
        window.draw(Isaac.getSprite());
        window.setView(getCordsForView(0, 0));
        
        window.display();
    }

    return 0;
}