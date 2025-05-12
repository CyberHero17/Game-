#include <iostream>
#include <memory>
#include <experimental/random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
int main(){
// Define a rectangle, located at (0, 0) with a size of 20x5
sf::FloatRect r1(0, 0, 20, 5);
 
// Define another rectangle, located at (4, 2) with a size of 18x10
sf::Vector2f position(4, 2);
sf::Vector2f size(18, 10);
sf::FloatRect r2(position, size);
 
// Test intersections with the point (3, 1)
bool b1 = r1.contains(3, 1); // true
bool b2 = r2.contains(3, 1); // false
 
// Test the intersection between r1 and r2
sf::FloatRect result;
bool b3 = r1.intersects(r2); // true
std::cout << b3;
// result == (4, 2, 16, 3)
return 0;
}