#include "sortowania.h"
void insertion(std::vector<int> wstawianie) {
    sf::RenderWindow wstawianko(sf::VideoMode(szerokosc, wysokosc), "Wstawianie", sf::Style::Resize);
    wstawianko.setFramerateLimit(60);
    wstawianko.setPosition(sf::Vector2i(0, 150));
    int i, key, j;
    bool skonczone = false;
    while (wstawianko.isOpen())
    {
        sf::Event t;
        while (wstawianko.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(wstawianko, wstawianie, 1);
                break;
            }
        if (!skonczone && start) {
            for (i = 1; i < wstawianie.size(); i++) {
                key = wstawianie[i];
                j = i - 1;
                while (j >= 0 && wstawianie[j] > key)
                {
                    wstawianie[j + 1] = wstawianie[j];
                    j = j - 1;
                    if (close)
                        break;
                    sf::Event e;
                    while (wstawianko.pollEvent(e))
                        if (e.type == sf::Event::Resized)
                            break;
                    rysuj(wstawianko, wstawianie, 1);
                }
                if (close)
                    break;
                wstawianie[j + 1] = key;
                rysuj(wstawianko, wstawianie, 1);
            }
            skonczone = true;
        }
        else
            rysuj(wstawianko, wstawianie, 1);
        if (close)
            wstawianko.close();
    }
}