#include "sortowania.h"
void heapify(sf::RenderWindow& kopiec, std::vector<int>& kopczyki, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && kopczyki[l] > kopczyki[largest])
        largest = l;
    rysuj(kopiec, kopczyki, 3);
    if (r < n && kopczyki[r] > kopczyki[largest])
        largest = r;
    rysuj(kopiec, kopczyki, 3);
    sf::Event t;
    while (kopiec.pollEvent(t))
        if (t.type == sf::Event::Resized) {
            rysuj(kopiec, kopczyki, 3);
            break;
        }
    if (largest != i && !close) {
        std::swap(kopczyki[i], kopczyki[largest]);
        rysuj(kopiec, kopczyki, 3);
        heapify(kopiec, kopczyki, n, largest);
    }
}
void heapsort_in(std::vector<int> kopczyki) {
    sf::RenderWindow kopiec(sf::VideoMode(szerokosc, wysokosc), "Heap sort", sf::Style::Resize);
    kopiec.setFramerateLimit(60);
    kopiec.setPosition(sf::Vector2i(0, 450));
    bool skonczone = false;
    while (kopiec.isOpen())
    {
        sf::Event t;
        while (kopiec.pollEvent(t))
            if (t.type == sf::Event::Resized) {
                rysuj(kopiec, kopczyki, 3);
                break;
            }
        if (!skonczone && start) {
            for (int i = kopczyki.size() / 2 - 1; i >= 0 && !close; i--)
                heapify(kopiec, kopczyki, kopczyki.size(), i);
            for (int i = kopczyki.size() - 1; i > 0 && !close; i--) {
                std::swap(kopczyki[0], kopczyki[i]);
                rysuj(kopiec, kopczyki, 3);
                heapify(kopiec, kopczyki, i, 0);
            }
            skonczone = true;
        }
        else
            rysuj(kopiec, kopczyki, 3);
        if (close)
            kopiec.close();
    }
}