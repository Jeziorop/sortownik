#include "visualisation.h"
#include <algorithm>
#include <string>
visualisation::visualisation(std::vector<int> &values)
{
	std::random_device rd;
	generator.seed(rd());
	this->values = values;
	colors.x = rand_int(0, 255);
	colors.y = rand_int(0, 255);
	variants.x = rand_int(0, 2);
	variants.y = rand_int(0, 1);
	assign_operation_count = 0;
	comparision_operation_count = 0;
	counter_font.loadFromFile("res\\Arial.ttf");
}
visualisation::visualisation(int size)
{
	std::random_device rd;
	generator.seed(rd());
	values.resize(size);
	for (int i = 0; i < size; ++i)
		values[i] = rand_int(0, 255);
	colors.x = rand_int(0, 255);
	colors.y = rand_int(0, 255);
	variants.x = rand_int(0, 2);
	variants.y = rand_int(0, 1);
	assign_operation_count = 0;
	comparision_operation_count = 0;
	counter_font.loadFromFile("res\\Arial.ttf");
}
void visualisation::bubble_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Bubble sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) {
				draw();
				break;
			}
		if (!finished)
		{
			for (int i = 0; i < values.size(); i++)
				for (int j = 1; j < values.size() - i; j++)
				{
					if (values[j - 1] > values[j])
					{
						assign_operation_count += 2;
						std::swap(values[j], values[j - 1]);
					}
					comparision_operation_count++;
					sf::Event e;
					while (window.pollEvent(e))
						if (e.type == sf::Event::Resized)
							break;
					draw();
				}
			finished = true;
		}
		else
			draw();
		
	}
}
void visualisation::insertion_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Insertion sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) {
				draw();
				break;
			}
		if (!finished) {
			for (int i = 1; i < values.size(); i++) {
				int key = values[i];
				int j = i - 1;
				while (j >= 0 && values[j] > key)
				{
					values[j + 1] = values[j];
					j = j - 1;
					sf::Event e;
					while (window.pollEvent(e))
						if (e.type == sf::Event::Resized)
							break;
					comparision_operation_count++;
					assign_operation_count++;
					draw();
				}
				values[j + 1] = key;
				assign_operation_count++;
				draw();
			}
			finished = true;
		}
		else
			draw();
	}
}
void visualisation::quick_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Quick sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) 
			{
				draw();
				break;
			}
		if (!finished) 
		{
			quick_sort_in(0, values.size() - 1);
			finished = true;
		}
		else
			draw();
	}
}
void visualisation::quick_sort_in(int low, int high)
{
	if (low >= high)
		return;
	int pivot = partition(low, high);

	quick_sort_in(low, pivot - 1);
	quick_sort_in(pivot + 1, high);
}
int visualisation::partition(int low, int high)
{
	int pivotValue = values[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized)
			{
				draw();
				break;
			}
		if (values[j] < pivotValue)
		{
			i++;
			std::swap(values[i], values[j]);
			assign_operation_count += 2;
		}
		comparision_operation_count++;
		draw();
	}

	std::swap(values[i + 1], values[high]);
	assign_operation_count += 2;
	draw();

	return i + 1;
}
void visualisation::draw()
{
	window.clear();
	float rect_width = float(window_width) / values.size();
	for (int i = 0; i < values.size(); ++i)
	{
		sf::RectangleShape temp_rect;
		temp_rect.setSize(sf::Vector2f(rect_width, values[i] / 256.f * 100.f));
		temp_rect.setFillColor(gradient(values[i]));
		temp_rect.setOrigin(sf::Vector2f(rect_width, values[i] / (256.f / window_height)));
		temp_rect.setPosition(sf::Vector2f((i + 1) * rect_width, window_height));
		window.draw(temp_rect);
	}
	sf::Text counter("assigns: " + std::to_string(assign_operation_count) + "\ncomparisions: " + std::to_string(comparision_operation_count), counter_font, 15);
	counter.setFillColor(sf::Color::White);
	counter.setPosition(sf::Vector2f(0.f, 0.f));
	counter.setOutlineThickness(1.f);
	window.draw(counter);
	window.display();
}
void visualisation::heap_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Heap sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(0, 450));
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) {
				draw();
				break;
			}
		if (!finished) {
			for (int i = values.size() / 2 - 1; i >= 0; i--)
				heapify(values.size(), i);
			for (int i = values.size() - 1; i > 0; i--) {
				std::swap(values[0], values[i]);
				assign_operation_count += 2;
				draw();
				heapify(i, 0);
			}
			finished = true;
		}
		else
			draw();
	}
}
void visualisation::heapify(int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && values[l] > values[largest])
		largest = l;
	comparision_operation_count++;
	draw();
	if (r < n && values[r] > values[largest])
		largest = r;
	comparision_operation_count++;
	draw();
	sf::Event t;
	while (window.pollEvent(t))
		if (t.type == sf::Event::Resized)
		{
			draw();
			break;
		}
	if (largest != i)
	{
		std::swap(values[i], values[largest]);
		assign_operation_count += 2;
		draw();
		heapify(n, largest);
	}
}
void visualisation::bogo_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Bogo sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) {
				draw();
				break;
			}
		if (!finished)
		{
			std::random_shuffle(values.begin(), values.end());
			finished = std::is_sorted(values.begin(), values.end());
		}
		draw();
		//if (finished)//close)
			//window.close();

	}
}
void visualisation::merge_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Merge sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) 
			{
				draw();
				break;
			}
		if (!finished) 
		{
			merge_sort_in(0, values.size() - 1);
			finished = true;
		}
		else
			draw();
	}
}
void visualisation::merge_sort_in(int begin, int end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	merge_sort_in(begin, mid);
	merge_sort_in(mid + 1, end);
	merge(begin, mid, end);
}
void visualisation::merge(int left, int mid, int right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
	{
		leftArray[i] = values[left + i];
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized)
			{
				draw();
				break;
			}
		assign_operation_count++;
		draw();
	}
	for (auto j = 0; j < subArrayTwo; j++)
	{
		rightArray[j] = values[mid + 1 + j];
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized)
			{
				draw();
				break;
			}
		assign_operation_count++;
		draw();
	}

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) 
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized)
			{
				draw();
				break;
			}
		comparision_operation_count++;
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) 
		{
			values[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			assign_operation_count++;
			draw();
			indexOfSubArrayOne++;
		}
		else 
		{
			values[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			assign_operation_count++;
			draw();
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized)
			{
				draw();
				break;
			}
		values[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		assign_operation_count++;
		draw();
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) 
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized)
			{
				draw();
				break;
			}
		values[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		assign_operation_count++;
		draw();
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}
void visualisation::comb_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Comb sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) {
				draw();
				break;
			}
		if (!finished)
		{
			int gap = values.size();
			bool swapped = true;

			while (gap != 1 || swapped)
			{
				gap = std::max((gap * 10) / 13, 1);

				swapped = false;
				for (int i = 0; i < values.size() - gap; i++)
				{
					sf::Event t;
					while (window.pollEvent(t))
						if (t.type == sf::Event::Resized) {
							draw();
							break;
						}
					comparision_operation_count++;
					if (values[i] > values[i + gap])
					{
						std::swap(values[i], values[i + gap]);
						assign_operation_count += 2;
						swapped = true;
					}
					draw();
				}
			}
			finished = true;
		}
		else
			draw();

	}
}
void visualisation::shell_sort()
{
	window.create(sf::VideoMode(window_width, window_height), "Shell sort", sf::Style::Resize);
	window.setFramerateLimit(60);
	bool finished = false;
	while (window.isOpen())
	{
		sf::Event t;
		while (window.pollEvent(t))
			if (t.type == sf::Event::Resized) {
				draw();
				break;
			}
		if (!finished)
		{
			for (int gap = values.size() / 2; gap > 0; gap /= 2)
				for (int i = gap; i < values.size(); i += 1) {
					int temp = values[i];
					int j;
					for (j = i; j >= gap && values[j - gap] > temp; j -= gap) {
						values[j] = values[j - gap];
						assign_operation_count++;
						comparision_operation_count++;
						sf::Event s;
						while (window.pollEvent(s))
							if (s.type == sf::Event::Resized) {
								draw();
								break;
							}
						draw();
					}
					values[j] = temp;
					comparision_operation_count++;
					draw();
				}
			finished = true;
		}
		else
			draw();

	}

}
sf::Color visualisation::gradient(int val)
{
	if (variants.y == 1)
		val = 256 - val;

	if (variants.x == 0)
		return sf::Color(val, colors.x, colors.y);
	else if (variants.x == 1)
		return sf::Color(colors.x, val, colors.y);
	else
		return sf::Color(colors.x, colors.y, val);
}
int visualisation::rand_int(int min, int maks)
{
	std::uniform_int_distribution<int> distribution(min, maks);
	return distribution(generator);
}