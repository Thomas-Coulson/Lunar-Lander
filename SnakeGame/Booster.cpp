#include "Booster.h"

Booster::Booster() :
	m_width(30),
	m_height(30),
	m_colour(sf::Color::Red)
{
	m_booster.setSize(sf::Vector2f(m_width, m_height));

}

void Booster::update(float shipAngle, sf::Vector2f shipPosition) {

	m_booster.setOrigin(15, -15);
	m_booster.setPosition(sf::Vector2f(shipPosition.x, shipPosition.y));
	m_booster.setRotation(shipAngle);

}

void Booster::render(sf::RenderWindow& window) {
	m_booster.setFillColor(m_colour);
	window.draw(m_booster);
}