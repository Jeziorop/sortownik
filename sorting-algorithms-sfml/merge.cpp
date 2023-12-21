#include "sortowania.h"
std::vector<int> pom;
void scal(sf::RenderWindow& app, std::vector<int>& tab, int lewy, int srodek, int prawy)
{
    int i = lewy, j = srodek + 1;
    for (int i = lewy; i <= prawy; i++)
        pom[i] = tab[i];
    for (int k = lewy; k <= prawy && !close; k++) {
        sf::Event t;
        while (app.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(app, tab, 5);
                break;
            }
        if (i <= srodek)
            if (j <= prawy)
                if (pom[j] < pom[i])
                    tab[k] = pom[j++];
                else
                    tab[k] = pom[i++];
            else
                tab[k] = pom[i++];
        else
            tab[k] = pom[j++];
        rysuj(app, tab, 5);
    }
}

void sortowanie_przez_scalanie(sf::RenderWindow& app, std::vector<int>& tab, int lewy, int prawy)
{
    if (prawy <= lewy || close) return;

    int srodek = (prawy + lewy) / 2;
    sortowanie_przez_scalanie(app, tab, lewy, srodek);
    sortowanie_przez_scalanie(app, tab, srodek + 1, prawy);
    scal(app, tab, lewy, srodek, prawy);
}
void mergesort_in(std::vector<int> laczonko) {
    pom.resize(laczonko.size());
    sf::RenderWindow merge(sf::VideoMode(szerokosc, wysokosc), "Merge sort", sf::Style::Resize);
    merge.setFramerateLimit(60);
    merge.setPosition(sf::Vector2i(0, 750));
    bool skonczone = false;
    while (merge.isOpen())
    {
        sf::Event t;
        while (merge.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(merge, laczonko, 5);
                break;
            }
        if (!skonczone && start) {
            sortowanie_przez_scalanie(merge, laczonko, 0, laczonko.size() - 1);
            skonczone = true;
        }
        else
            rysuj(merge, laczonko, 5);
        if (close) {
            merge.setActive(false);
            merge.close();
        }
    }
}