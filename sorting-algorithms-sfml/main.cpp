//#include "sortowania.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "visualisation.h"
#include "gui.h"
#include <thread>
#include <chrono>
sf::Font global_font;
int main()
{
    global_font.loadFromFile("res//Arial.ttf");
    gui GUI;
    GUI.start();
}