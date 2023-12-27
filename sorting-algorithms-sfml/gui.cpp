#include "gui.h"
#include <iostream>

gui::gui()
{
	font.loadFromFile("res\\Arial.ttf");
	current_state = view_state::Mainview;
	visualisations_list_header.setString("current visualisations");
	visualisations_list_header.setCharacterSize(30);
	visualisations_list_header.setPosition(100.f, 50.f);
	visualisations_list_header.setFillColor(sf::Color::White);
	visualisations_list_header.setFont(font);
	add_visualisation_button = text_rectangle("Add", 20, sf::Color(50, 50, 50), sf::Vector2f(300.f, 50.f), 10.f);
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
	window.draw(add_visualisation_button.background);
	window.draw(add_visualisation_button.text);
	window.display();
}
void gui::handle_events()
{
	sf::Event t;
	while(window.pollEvent(t))
		if (t.type == sf::Event::Resized) {
			draw();
			break;
		}
}