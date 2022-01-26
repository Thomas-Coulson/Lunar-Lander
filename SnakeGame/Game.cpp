#include "Game.h"

Game::Game(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_gravityAcceleration(0.03),
	m_gravityMaxAcc(2),
	m_shipFall(false)
{
	buildObjects();
}

void Game::buildObjects() {

}

void Game::update() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_shipFall = true;
	}

	if (m_shipFall) {
		if (m_player.getVelocityY() <= m_gravityMaxAcc) {
			m_player.setVelocityY(m_player.getVelocityY() + m_gravityAcceleration);
		}
	}
	else {
		m_player.setVelocityY(0);
	}

	m_player.update(m_windowWidth);
}

void Game::render(sf::RenderWindow& window) {
	m_player.render(window);
}