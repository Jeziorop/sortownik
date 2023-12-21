#include "sortowania.h"
#include <chrono>
#include <thread>
sf::Color barwa(int &id, int wartosc) {
    if (konfiguracja[id].second == 1)
        wartosc = 256 - wartosc;
    if (konfiguracja[id].first == 0)
        return sf::Color(wartosc, kolory[id].first, kolory[id].second);
    else if(konfiguracja[id].first == 1)
        return sf::Color(kolory[id].first, wartosc, kolory[id].second);
    else if(konfiguracja[id].first == 2)
        return sf::Color(kolory[id].first, kolory[id].second, wartosc);
}
void rysuj(sf::RenderWindow& okno, std::vector<int> &arr, int id) {
    okno.clear();
    for (int k = 1; k <= arr.size(); k++) {
        sf::RectangleShape slup(sf::Vector2f(szerokosc_rect, arr[k - 1] / (256.0 / wysokosc)));
        slup.setFillColor(barwa(id, arr[k - 1]));
        slup.setOrigin(sf::Vector2f(szerokosc_rect, arr[k - 1] / (256.0 / wysokosc)));
        slup.setPosition(sf::Vector2f(k * szerokosc_rect, wysokosc));
        okno.draw(slup);
    }
    okno.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}