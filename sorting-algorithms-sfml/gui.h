#pragma once
#include <SFML/Graphics.hpp>
#include "visualisation.h"
#include "view_state.h"
#include "text_rectangle.h"
#include <vector>
#include <thread>
class gui
{
private:
	const float window_width;
	const float window_height;
	sf::RenderWindow window;
	std::vector<std::shared_ptr<visualisation>> visualisations;
	std::vector<std::thread> running_threads;
	std::vector<void (visualisation::*)()> algorithms_ptr;
	view_state current_state;
	//Mainview components
	sf::Text visualisations_list_header;
	std::vector<text_rectangle> visualisations_list;
	text_rectangle add_button;
	text_rectangle run_button;
	text_rectangle end_button;
	//Createview components
	std::vector<text_rectangle> algorithms_to_choose;
	int chosen;
	sf::Text array_size_input;
	int array_size;
	text_rectangle create_button;
public:
	gui();
	void start();
	void run_visualisations();
	void run_visualisations(unsigned int id);
	void end_visualisations();
	void end_visualisations(unsigned int id);
	void handle_events();
	void draw();
	void create_visualisation();
};

