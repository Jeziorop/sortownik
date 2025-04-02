#pragma once
#include <SFML/Graphics.hpp>
struct text_rectangle
{
    sf::RectangleShape background;
    sf::Text text;
    float padding;
    text_rectangle();
    text_rectangle(const sf::Font *font);
    text_rectangle(const sf::Font *font, const sf::String text_string, unsigned int character_size, const sf::Color bg_color, const sf::Vector2f position, const float padding);
    void set_position(const sf::Vector2f position);
    void set_text(const sf::String text_string);
    bool is_collision(const int& x, const int& y);
};