#include "gui.h"
extern sf::Font* global_font;
gui::gui()
	: window_height(500), window_width(500), current_state(view_state::Mainview), add_button("Add", 20, sf::Color(50, 50, 50), sf::Vector2f(400.f, 48.f), 10.f), array_size(0), algorithms_ptr({ &visualisation::bubble_sort, &visualisation::insertion_sort, &visualisation::quick_sort, &visualisation::heap_sort, &visualisation::bogo_sort, &visualisation::merge_sort, &visualisation::comb_sort, &visualisation::shell_sort, &visualisation::dumb_sort }), create_button("create", 20, sf::Color(50, 50, 50), sf::Vector2f(300.f, 300.f), 10.f), chosen(0), run_button("Run", 20, sf::Color(50, 50, 50), sf::Vector2f(50.f, 400.f), 10.f), end_button("End", 20, sf::Color(50, 50, 50), sf::Vector2f(400.f, 400.f), 10.f)
{
	visualisations_list_header.setString("current visualisations");
	visualisations_list_header.setCharacterSize(30);
	visualisations_list_header.setPosition(100.f, 50.f);
	visualisations_list_header.setFillColor(sf::Color::White);
	visualisations_list_header.setFont(*global_font);
	array_size_input.setString("No. elements: 100");
	array_size_input.setCharacterSize(20);
	array_size_input.setPosition(250.f, 120.f);
	array_size_input.setFillColor(sf::Color::White);
	array_size_input.setFont(*global_font);
	std::vector<std::string> algorithms_names = { "Bubble sort", "Insertion sort", "Quick sort", "Heap sort", "Bogo sort", "Merge sort", "Comb sort", "Shell sort", "Dumb sort" };
	for (int i = 0; i < algorithms_names.size(); ++i)
	{
		text_rectangle option(algorithms_names[i], 15, sf::Color(50, 50, 50), sf::Vector2f(30, 30 + 50 * i), 10.f);
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
		if (window.isOpen())
			draw();
	}
}
void gui::draw()
{
	window.clear(sf::Color(60, 60, 60));
	switch (current_state)
	{
	case view_state::Mainview:
		window.draw(visualisations_list_header);
		if (visualisations.empty())
		{
			text_rectangle empty("(empty)", 20, sf::Color(50, 50, 50), sf::Vector2f(200.f, 100.f), 10.f);
			window.draw(empty.background);
			window.draw(empty.text);
		}
		else
		{
			for (int i = 0; i < visualisations_list.size(); ++i)
			{
				visualisations_list[i].text.setString(visualisations[i]->get_title());
				window.draw(visualisations_list[i].background);
				window.draw(visualisations_list[i].text);
			}
		}
		if (visualisations.size() < 5)
		{
			window.draw(add_button.background);
			window.draw(add_button.text);
		}
		window.draw(run_button.background);
		window.draw(run_button.text);
		window.draw(end_button.background);
		window.draw(end_button.text);
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
			break;
		}
		else if (t.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			int x = pos.x;
			int y = pos.y;
			switch (current_state)
			{
			case view_state::Mainview:
				for (int i = 0; i < visualisations_list.size(); ++i)
					if (visualisations_list[i].is_collision(x, y))
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							run_visualisations(i);
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
							end_visualisations(i);
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
							visualisations[i]->roll_colors();
					}
				if (add_button.is_collision(x, y) && visualisations.size() < 5)
				{
					current_state = view_state::Createview;
					array_size_input.setString("No. elements: 100");
					array_size = 100;
					chosen = 0;
				}
				else if (run_button.is_collision(x, y))
					run_visualisations();
				else if (end_button.is_collision(x, y))
					end_visualisations();
				break;

			case view_state::Createview:
				if (create_button.is_collision(x, y))
					create_visualisation();

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
			case view_state::Mainview:

				break;
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
void gui::run_visualisations(unsigned int id)
{
	if (id >= visualisations.size())
		return;
	visualisations[id]->set_state(visualisation_state::Running);
}
void gui::end_visualisations()
{
	for (auto const& vis : visualisations)
		vis->set_state(visualisation_state::Closed);
	for (auto& thread : running_threads)
		thread.join();
	visualisations.clear();
	running_threads.clear();
	visualisations_list.clear();
}
void gui::end_visualisations(unsigned int id)
{
	if (id >= visualisations.size())
		return;
	visualisations_list.erase(visualisations_list.begin() + id);
	visualisations[id]->set_state(visualisation_state::Closed);
	running_threads[id].join();
	running_threads.erase(running_threads.begin() + id);
	visualisations.erase(visualisations.begin() + id);
	for (int i = id; i < visualisations_list.size(); ++i)
	{
		visualisations_list[i].set_position(sf::Vector2f(135.f, 100.f + 60.f * i));
		visualisations[i]->set_position(sf::Vector2i(0, 137 * i));
	}
}
void gui::create_visualisation()
{
	current_state = view_state::Mainview;
	visualisations.emplace_back(std::make_shared<visualisation>(array_size, sf::Vector2i(0, 137 * visualisations.size())));
	running_threads.emplace_back(algorithms_ptr[chosen], visualisations.back());
	array_size_input.setString("No. elements: 100");
	visualisations_list.emplace_back("", 20, sf::Color(50, 50, 50), sf::Vector2f(135.f, 100.f + 60.f * visualisations_list.size()), 10.f);
	visualisations_list.back().background.setSize(sf::Vector2f(230.f, 50.f));
	array_size = 100;
	chosen = 0;
}