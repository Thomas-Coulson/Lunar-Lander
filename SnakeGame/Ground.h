#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

class Ground
{
private:
	std::vector<sf::Vector2f> m_allPoints;
	std::vector<sf::Vector2f> m_landingIndexes;
public:
	Ground();
	void render(sf::RenderWindow& window);
	std::vector<sf::Vector2f> getGpoints() { return m_allPoints; }
	std::vector<sf::Vector2f> getLandingIndexes() { return m_landingIndexes; }
};

