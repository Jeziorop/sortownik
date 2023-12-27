#pragma once
#include <SFML/Graphics.hpp>
#include "visualisation.h"
#include "view_state.h"
#include "text_rectangle.h"
#include <vector>
#include <set>
class gui
{
private:
	const float window_width = 500.f;
	const float window_height = 500.f;
	sf::RenderWindow window;
	std::set<std::unique_ptr<visualisation>> visualisations;
	view_state current_state;
	sf::Font font;
	//Mainview components
	sf::Text visualisations_list_header;
	text_rectangle add_visualisation_button;
	//Createview components
	//std::vector<text_rectangle> algorithms_to_choose;
public:
	gui();
	void start();
	void handle_events();
	void draw();
};

