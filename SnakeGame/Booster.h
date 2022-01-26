#pragma once
#include <SFML/Graphics.hpp>

class Booster
{
private:
	sf::RectangleShape m_booster;
	int m_width;
	int m_height;
	sf::Color m_colour;
public:
	Booster();
	void update(float shipAngle, sf::Vector2f shipPosition);
	void render(sf::RenderWindow& window);
};

