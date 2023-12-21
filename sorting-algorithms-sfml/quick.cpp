#include "sortowania.h"
void quick_sort(sf::RenderWindow& quick, std::vector<int>& quiczek, int lewy, int prawy)
{
    if (prawy <= lewy) return;

    int i = lewy - 1, j = prawy + 1,
        pivot = quiczek[(lewy + prawy) / 2];
    while (1)
    {
        while (pivot > quiczek[++i]);
        while (pivot < quiczek[--j]);
        if (i <= j) {
            std::swap(quiczek[i], quiczek[j]);
            rysuj(quick, quiczek, 2);
            if (close)
                break;
            sf::Event t;
            while (quick.pollEvent(t))
                if (t.type == sf::Event::Resized) {
                    rysuj(quick, quiczek, 2);
                    break;
                }
        }
        else
            break;
    }
    if (!close) {
        if (j > lewy)
            quick_sort(quick, quiczek, lewy, j);
        if (i < prawy)
            quick_sort(quick, quiczek, i, prawy);
    }
}
void quicksort_in(std::vector<int> quiczek) {
    sf::RenderWindow quick(sf::VideoMode(szerokosc, wysokosc), "Quick-sort", sf::Style::Resize);
    quick.setFramerateLimit(60);
    quick.setPosition(sf::Vector2i(0, 300));
    bool skonczone = false;
    while (quick.isOpen())
    {
        sf::Event t;
        while (quick.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(quick, quiczek, 2);
                break;
            }
        if (!skonczone && start) {
            quick_sort(quick, quiczek, 0, quiczek.size() - 1);
            skonczone = true;
        }
        else
            rysuj(quick, quiczek, 2);
        if (close)
            quick.close();
    }
}