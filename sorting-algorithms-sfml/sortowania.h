#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
void bubblesort(std::vector<int> babelkowe);
void insertion(std::vector<int> wstawianie);
void quicksort_in(std::vector<int> quiczek);
void heapsort_in(std::vector<int> kopczyki);
void Shellsort(std::vector<int> muszelki);
void mergesort_in(std::vector<int> laczonko);
void combsort(std::vector<int> grzebieniowe);
void rysuj(sf::RenderWindow& okno, std::vector<int> &arr, int id);
extern int szerokosc, wysokosc;
extern float szerokosc_rect;
extern bool close, start;
extern std::vector<std::pair<int, int>> kolory;
extern std::vector<std::pair<int, int>> konfiguracja;