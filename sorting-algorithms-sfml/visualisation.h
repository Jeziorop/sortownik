#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
class visualisation
{
private:
	std::mt19937 generator;
	static const int window_width = 1000;
	static const int window_height = 100;
	std::vector<int> values;
	sf::Vector2i colors;
	sf::Vector2i variants;
	sf::RenderWindow window;

public:
	visualisation(std::vector<int>& values);
	visualisation(int size);
	void bubble_sort();
	void insertion_sort();
	void quick_sort();
	void heap_sort();
	void bogo_sort();
	void merge_sort();
	void comb_sort();
	void shell_sort();
private:
	void quick_sort_in(int low, int high);
	int partition(int low, int high);
	void heapify(int n, int i);
	void merge(int left, int mid, int right);
	void merge_sort_in(int begin, int end);
	sf::Color gradient(int val);
	void draw();
	int rand_int(int min, int max);
};

