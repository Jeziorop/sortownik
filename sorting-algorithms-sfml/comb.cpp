#include "sortowania.h"
int getNextGap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap < 1)
        return 1;
    return gap;
}
void combsort(std::vector<int> grzebieniowe) {
    sf::RenderWindow grzebien(sf::VideoMode(szerokosc, wysokosc), "Grzebieniowe", sf::Style::Resize);
    grzebien.setFramerateLimit(60);
    grzebien.setPosition(sf::Vector2i(0, 900));
    int i = 0, j = 1;
    bool skonczone = false;
    while (grzebien.isOpen())
    {
        sf::Event t;
        while (grzebien.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(grzebien, grzebieniowe, 0);
                break;
            }
        if (!skonczone && start)
        {
            int n = grzebieniowe.size();
            int gap = n;
            bool swapped = true;
            while ((gap != 1 || swapped == true) && !close)
            {
                gap = getNextGap(gap);
                swapped = false;
                for (int i = 0; i < n - gap; i++)
                {
                    sf::Event t;
                    while (grzebien.pollEvent(t))
                        if (t.type == sf::Event::Resized) {
                            rysuj(grzebien, grzebieniowe, 0);
                            break;
                        }
                    if (grzebieniowe[i] > grzebieniowe[i + gap])
                    {
                        std::swap(grzebieniowe[i], grzebieniowe[i + gap]);
                        rysuj(grzebien, grzebieniowe, 6);
                        swapped = true;
                    }
                }
            }
            skonczone = true;
        }
        else
            rysuj(grzebien, grzebieniowe, 6);
        if (close) 
        {
            grzebien.setActive(false);
            grzebien.close();
        }
    }
}