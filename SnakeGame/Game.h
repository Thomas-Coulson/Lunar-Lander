#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Game
{
private:
	int m_windowWidth;
	int m_windowHeight;
	Ship m_player;
	float m_gravityAcceleration;
	float m_gravityMaxAcc;
	bool m_shipFall;
public:
	Game(int windowWidth, int windowHeight);
	void buildObjects();
	void update();
	void render(sf::RenderWindow& window);
};

