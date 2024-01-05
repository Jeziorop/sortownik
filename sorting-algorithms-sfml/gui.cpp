#include "gui.h"
#include <iostream>

gui::gui()
	: window_height(500), window_width(500), current_state(view_state::Mainview), add_button("Add", 20, sf::Color(50, 50, 50), sf::Vector2f(300.f, 50.f), 10.f), array_size(0), algorithms_ptr({ &visualisation::bubble_sort, &visualisation::insertion_sort, &visualisation::quick_sort, &visualisation::heap_sort, &visualisation::bogo_sort, &visualisation::merge_sort, &visualisation::comb_sort, &visualisation::shell_sort }), create_button("create", 20, sf::Color(50, 50, 50), sf::Vector2f(300.f, 300.f), 10.f)
{
	font.loadFromFile("res\\Arial.ttf");
	visualisations_list_header.setString("current visualisations");
	visualisations_list_header.setCharacterSize(30);
	visualisations_list_header.setPosition(100.f, 50.f);
	visualisations_list_header.setFillColor(sf::Color::White);
	visualisations_list_header.setFont(font);
	array_size_input.setString("No. elements: 100");
	array_size_input.setCharacterSize(20);
	array_size_input.setPosition(200, 50);
	array_size_input.setFillColor(sf::Color::White);
	array_size_input.setFont(font);
	std::vector<std::string> algorithms_names = { "Bubble sort", "Insertion sort", "Quick sort", "Heap sort", "Bogo sort", "Merge sort", "Comb sort", "Shell sort" };
	for (int i = 0; i < algorithms_names.size(); ++i)
	{
		text_rectangle option(algorithms_names[i], 15, sf::Color(50, 50, 50), sf::Vector2f(30, 80 + 50 * i), 10.f);
		option.background.setSize(sf::Vector2f(120, 40));
		algorithms_to_choose.emplace_back(option);
	}
}
void gui::start()
{
	window.create(sf::VideoMode(window_width, window_height), "Menu", sf::Style::Close);
	while (window.isOpen())
	{
		handle_events();
		draw();
	}
}
void gui::draw()
{
	window.clear(sf::Color::Blue);
	switch (current_state)
	{
	case view_state::Mainview:
		window.draw(visualisations_list_header);
		if (visualisations.empty())
		{
			text_rectangle empty("(empty)", 20, sf::Color(50, 50, 50), sf::Vector2f(150.f, 80.f), 10.f);
			window.draw(empty.background);
			window.draw(empty.text);
		}
		else
		{
			text_rectangle visualisation_name;
			for (const auto& ptr : visualisations)
			{
				std::cout << std::string(ptr->get_title()) << '\n';
			}
		}
		window.draw(add_button.background);
		window.draw(add_button.text);
		break;

	case view_state::Createview:
		window.draw(create_button.background);
		window.draw(create_button.text);
		window.draw(array_size_input);
		for (int i = 0; i < algorithms_to_choose.size(); ++i)
		{
			if (i == chosen)
				algorithms_to_choose[i].background.setFillColor(sf::Color(20, 20, 20));
			else
				algorithms_to_choose[i].background.setFillColor(sf::Color(50, 50, 50));
			window.draw(algorithms_to_choose[i].background);
			window.draw(algorithms_to_choose[i].text);
		}
		break;
	}
	window.display();
}
void gui::handle_events()
{
	sf::Event t;
	while (window.pollEvent(t))
		if (t.type == sf::Event::Closed) {
			end_visualisations();
			window.close();
		}
		else if (t.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			int x = pos.x;
			int y = pos.y;
			switch (current_state)
			{
			case view_state::Mainview:
				if (add_button.is_collision(x, y))
				{
					current_state = view_state::Createview;
					array_size = 100;
					chosen = 0;
				}
				break;

			case view_state::Createview:
				if (create_button.is_collision(x, y))
				{
					current_state = view_state::Mainview;
					visualisations.emplace_back(std::make_shared<visualisation>(array_size));
					running_threads.emplace_back(algorithms_ptr[chosen], visualisations.back());
					array_size = 100;
					chosen = 0;
				}
				for (int i = 0; i < algorithms_to_choose.size(); ++i)
					if (algorithms_to_choose[i].is_collision(x, y))
					{
						chosen = i;
						break;
					}
				break;
			}
		}
		else if (t.type == sf::Event::KeyPressed)
		{
			switch (current_state)
			{
			case view_state::Createview:
				std::string input_string = array_size_input.getString();
				if (sf::Keyboard::Key::Num0 <= t.key.code && t.key.code <= sf::Keyboard::Key::Num9 && array_size < 1e3)
				{
					if (t.key.code == sf::Keyboard::Key::Num0 && array_size == 0)
						continue;
					array_size_input.setString(input_string + char(t.key.code - sf::Keyboard::Key::Num0 + '0'));
					array_size = array_size * 10 + t.key.code - sf::Keyboard::Key::Num0;
				}
				else if (t.key.code == sf::Keyboard::Key::BackSpace && array_size > 0)
				{
					input_string.pop_back();
					array_size_input.setString(input_string);
					array_size /= 10;
				}
			}
		}
}
void gui::run_visualisations()
{
	for (auto const& vis : visualisations)
		vis->set_state(visualisation_state::Running);
}
void gui::end_visualisations()
{
	for (auto const& vis : visualisations)
		vis->set_state(visualisation_state::Closed);
	for (auto& thread : running_threads)
		thread.join();
	visualisations.clear();
	running_threads.clear();
}