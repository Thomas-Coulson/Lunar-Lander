#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

class Ship
{
private:
	std::vector<sf::Vector2f> m_allPoints;
	std::vector<sf::Vector2f> m_shipPoints;
	std::vector<sf::Vector2f> m_boostPoints;
	sf::Vector2f m_velocity;
	float m_angle;
	float m_totalAngle;
	float m_maxSpeed;
	float m_acceleration;
	int m_boostAmount;
	bool m_boosterActive;
	bool m_landed;
	int m_landRotate;
	bool m_exploaded;

	int m_startX;
	int m_startY;

	bool m_menuActive = true;

	sf::Vector2f m_leftVelocity;
	sf::Vector2f m_topVelocity;
	sf::Vector2f m_rightVelocity;

public:
	Ship(float x, float y);
	sf::Vector2f rotatePoint(sf::Vector2f pointA, sf::Vector2f pointB, float angle);
	void update(float gravity, float maxGravity);
	void checkCollision(std::vector<sf::Vector2f> groundPoints, std::vector<sf::Vector2f> landingIndexes);
	float getLength(sf::Vector2f ground1, sf::Vector2f ground2);
	void render(sf::RenderWindow& window);

	void reset();

	bool getMenuActive() const { return m_menuActive; }
	bool getLanded() const { return m_landed; }
	bool getExploded() const { return m_exploaded; }
	int getBoostAmount() const { return m_boostAmount; }
	sf::Vector2f getVelocity() const { return m_velocity; }
};

