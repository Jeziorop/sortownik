#include "sortowania.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <thread>
#include <iostream>
int szerokosc = 1000, wysokosc = 100;
bool close = false, start;
std::vector<std::pair<int, int>> kolory(7, { 0, 0 });
std::vector<std::pair<int, int>> konfiguracja(7, { 0, 0 });
std::vector<std::thread> watki(7);
float szerokosc_rect;
int main()
{
    typedef void(*FunctionPointer)(std::vector<int>);
    FunctionPointer funkcje[] = {bubblesort, insertion, quicksort_in, heapsort_in, Shellsort, mergesort_in, combsort};
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::string komenda;
    std::cout << "Aby uzyskac pomoc wpisz w dowolnym miejscu 'help'.\n";
    while (true) {
        int n = 0;
        std::cout << "\nPodaj rozmiar sortowanej tablicy.\n";
        do
        {
            std::cin >> komenda;
            if (komenda == "help")
                std::cout << "\nPodana liczba musi miescic sie w zakresie [2, 10000].\n\nPodaj rozmiar sortowanej tablicy.\n";
            for (char z : komenda)
                if (z > 47 && z < 58)
                    n = n * 10 + z - 48;
            if (n > 10000) {
                std::cout << "Liczbe zredukowano do ";
                while (n > 10000)
                    n = n / 10;
                std::cout << n << ".\n";
            }
        } while (n < 1 && n <= 10000);
        std::vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 256;
        szerokosc_rect = 1.0 * szerokosc / n;
        std::cout << "\nKtore sortowania maja sie wykonac?\n";
        start = false;
        do
        {
            std::cin >> komenda;
            char klucz = '@';
            for (char zn : komenda)
                if (48 <= zn && zn <= 54) {
                    klucz = zn;
                    break;
                }
            if (klucz != '@') {
                klucz -= 48;
                kolory[klucz].first = rand() % 256, kolory[klucz].second = rand() % 256;
                konfiguracja[klucz].first = rand() % 3, konfiguracja[klucz].second = rand() % 2;
                if (!watki[klucz].joinable())
                    watki[klucz] = std::thread(funkcje[klucz], arr);
            }
            else if (komenda == "start")
                start = true;
            else if (komenda == "close")
                close = true;
            else if (komenda == "help")
                std::cout << "\nBy zakonczyc te sesje wpisz 'close'.\n\nWpisz wybrane przez Ciebie numery.\nbubble sort\t'0'\ninsertion sort\t'1'\nquick-sort\t'2'\nheap sort\t'3'\nshell sort\t'4'\nmerge sort\t'5'\nNa koniec wprowadzania wpisz 'start'.\nW celu zmiany palety kolorow wpisz ponownie odpowiedni numer z listy.\n\nKtore sortowania maja sie wykonac?\n";
        } while (!close);
        for (int i = 0; i < watki.size(); i++)
            if(watki[i].joinable())
                watki[i].join();
        close = false;
    }
    return 0;
}