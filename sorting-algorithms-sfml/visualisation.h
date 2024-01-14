#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <mutex>
#include "visualisation_state.h"
class visualisation
{
private:
	std::mutex window_access_mutex;
	visualisation_state program_state;
	static const int window_width = 1000;
	static const int window_height = 100;
	sf::Vector2i window_position;
	sf::RenderWindow window;
	std::string title;
	sf::String current_algorithm_name;
	std::vector<int> values;
	sf::Vector2i colors;
	sf::Vector2i variants;
	long long assign_operation_count;
	long long comparision_operation_count;
public:
	visualisation(const std::vector<int>& values, sf::Vector2i pos);
	visualisation(int size, sf::Vector2i pos);
	void bubble_sort();
	void insertion_sort();
	void quick_sort();
	void heap_sort();
	void bogo_sort();
	void merge_sort();
	void comb_sort();
	void shell_sort();
	void set_state(visualisation_state);
	std::string get_title();
	void set_position(sf::Vector2i pos);
private:
	void quick_sort_in(int low, int high);
	int partition(int low, int high);
	void heapify(int n, int i);
	void merge(int left, int mid, int right);
	void merge_sort_in(int begin, int end);
	sf::Color gradient(int val);
	void draw();
	void handle_events();
};

