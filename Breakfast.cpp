#include "Breakfast.hpp"
#include "GlobalVariables.hpp"
Breakfast::Breakfast(Vector2D coord)
{
    ispicked = 0;
    PedestalTexture.loadFromFile("Textures/Pedestal.png"); // это глобальные переменные
    BreakfastTexture.loadFromFile("Textures/Breakfast.png");
    this->coord = coord;

    PedestalSprite.setTexture(PedestalTexture); PedestalSprite.setPosition(coord.x - 24, coord.y - 16);
    ItemSprite.setTexture(BreakfastTexture); ItemSprite.setPosition(coord.x - 14 - 16,coord.y - 48 -16);
    
    id = 1;
    name = "Breakfast";
    collider_size = 20;

}

void Breakfast::pick(Player &pl)
{
    pl.HPContCount += 1;
    pl.health += 1;
    if (pl.health < pl.HPContCount)
    {
        pl.health += 1;
    }
    ispicked = 1;
    pl.GettingItem = 1;
    pl.GettingItemTime.restart();
}

void Breakfast::draw(sf::RenderWindow &window)
{
    float time = PickedTime.getElapsedTime().asMilliseconds();
    window.draw(PedestalSprite);
    if(not ispicked)
    {
        window.draw(ItemSprite);
    }
    if(ispicked && time < 1500)
    {
        window.draw(ItemSprite);
    }
}

void Breakfast::turn(Player &pl)
{
    float time = this->AnimationTime.getElapsedTime().asMilliseconds() * 0.003;
    ItemSprite.setPosition(coord.x - (int)(pl.SizeX * 0.5) - 14, coord.y - 16 - (int)(pl.SizeY * 1.5) + 10 * sin(time) ); // движение вверх-вниз
    Vector2D vect_to_pl = pl.coord - this->coord;
    if(not ispicked)
    {
        
        if (vect_to_pl.ModuleQuadr() <= collider_size * collider_size)
        {
            pick(pl);
            PickedTime.restart();
            
        }
    }

    if (  vect_to_pl.ModuleQuadr() < collider_size * collider_size)
    {
        Vector2D dV = 1/vect_to_pl.ModuleQuadr() * vect_to_pl; 
        pl.velocity = pl.velocity + 5*dV;
    }

    if (ispicked)
    {
        float time = PickedTime.getElapsedTime().asMilliseconds();
        if(time < 1500)
        {
            ItemSprite.setPosition(pl.coord.x - 20, pl.coord.y - 80);
        }
    }

    
}
