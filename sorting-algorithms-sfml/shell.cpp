#include "sortowania.h"
void Shellsort(std::vector<int> muszelki) {
    sf::RenderWindow stacja_paliw(sf::VideoMode(szerokosc, wysokosc), "ShellSort", sf::Style::Resize);
    stacja_paliw.setFramerateLimit(60);
    stacja_paliw.setPosition(sf::Vector2i(0, 600));
    bool skonczone = false;
    while (stacja_paliw.isOpen())
    {
        sf::Event t;
        while (stacja_paliw.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(stacja_paliw, muszelki, 4);
                break;
            }
        if (!skonczone && start) {
            for (int gap = muszelki.size() / 2; gap > 0 && !close; gap /= 2)
                for (int i = gap; i < muszelki.size(); i += 1){
                    int temp = muszelki[i];
                    int j;
                    sf::Event s;
                    while (stacja_paliw.pollEvent(s))
                        if (s.type == sf::Event::Resized) {
                            rysuj(stacja_paliw, muszelki, 4);
                            break;
                        }
                    if (close)
                        break;
                    for (j = i; j >= gap && muszelki[j - gap] > temp; j -= gap) {
                        muszelki[j] = muszelki[j - gap];
                        rysuj(stacja_paliw, muszelki, 4);
                    }
                    muszelki[j] = temp;
                    rysuj(stacja_paliw, muszelki, 4);
                }
            skonczone = true;
        }
        else
            rysuj(stacja_paliw, muszelki, 4);
        if (close)
            stacja_paliw.close();
    }
}