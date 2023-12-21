#include "sortowania.h"
void bubblesort(std::vector<int> babelkowe) {
    sf::RenderWindow bombel(sf::VideoMode(szerokosc, wysokosc), "Babelkowe", sf::Style::Resize);
    bombel.setFramerateLimit(60);
    bombel.setPosition(sf::Vector2i(0, 0));
    int i = 0, j = 1;
    bool skonczone = false;
    while (bombel.isOpen())
    {
        sf::Event t;
        while (bombel.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(bombel, babelkowe, 0);
                break;
            }
        if (!skonczone && start) {
            for (int i = 0; i < babelkowe.size(); i++)
                for (int j = 1; j < babelkowe.size() - i && !close; j++)
                    if (babelkowe[j - 1] > babelkowe[j]) {
                        std::swap(babelkowe[j - 1], babelkowe[j]);
                        rysuj(bombel, babelkowe, 0);
                        sf::Event e;
                        while (bombel.pollEvent(e))
                            if (e.type == sf::Event::Resized)
                                break;
                    }
            skonczone = true;
        }
        else
            rysuj(bombel, babelkowe, 0);
        if (close) {
            bombel.setActive(false);
            bombel.close();
        }
    }
}