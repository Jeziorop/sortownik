#include <SFML/Graphics.hpp>
#include "visualisation.h"
#include "gui.h"
//cheesy globals, but I didn't know where to put them
sf::Font global_font;
std::mt19937 generator;
int rand_int(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
int WinMain()
{
    global_font.loadFromFile("res//Arial.ttf");
    std::random_device rd;
    generator.seed(rd());
    gui GUI;
    GUI.start();
}