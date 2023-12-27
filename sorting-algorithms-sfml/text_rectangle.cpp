#include "text_rectangle.h"
extern sf::Font global_font;
text_rectangle::text_rectangle()
{
    //font.loadFromFile("res\\Arial.ttf");
    padding = 10.f;
    text.setFont(global_font);
    text.setCharacterSize(15);
    text.setString("");
    background.setFillColor(sf::Color(50, 50, 50));
    background.setSize(sf::Vector2f(text.getLocalBounds().width + 2 * padding, text.getLocalBounds().height + padding + text.getCharacterSize()));
}
text_rectangle::text_rectangle(const sf::String text_string = "", unsigned int character_size = 10, const sf::Color bg_color = sf::Color::Black, const sf::Vector2f position = sf::Vector2f(0.f, 0.f), float const padding = 10.f)
{
    //font.loadFromFile("res\\Arial.ttf");
    this->padding = padding;
    text = sf::Text(text_string, global_font, character_size);
    float textX = position.x + padding;
    float textY = position.y + padding;
    background.setSize(sf::Vector2f(text.getLocalBounds().width + 2 * padding, text.getLocalBounds().height + padding + text.getCharacterSize()));//approximately centered
    background.setFillColor(bg_color);
    background.setPosition(position);
    text.setPosition(textX, textY);
}
void text_rectangle::set_position(const sf::Vector2f position)
{
    background.setPosition(position);
    text.setPosition(position.x + padding, position.y + padding);
}
void text_rectangle::set_text(const sf::String text_string)
{
    text.setString(text_string);
    background.setSize(sf::Vector2f(text.getLocalBounds().width + 2 * padding + text.getCharacterSize(), text.getLocalBounds().height + 2 * padding + text.getCharacterSize()));
}