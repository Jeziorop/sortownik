#include "gui.h"
//cheesy global, but I didn't know where to put it
std::mt19937 generator;
int rand_int(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
int WinMain()
{
    std::random_device rd;
    generator.seed(rd());

    gui GUI;
    GUI.run();

    return 0;
}