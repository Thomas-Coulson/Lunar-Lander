#include "Ground.h"

Ground::Ground() {
    //set all ground points
    sf::Vector2f ground1 = sf::Vector2f(0, 425);
    m_allPoints.push_back(ground1);

    sf::Vector2f ground2 = sf::Vector2f(120, 450);
    m_allPoints.push_back(ground2);

    sf::Vector2f ground3 = sf::Vector2f(220, 500);
    m_allPoints.push_back(ground3);

    sf::Vector2f ground4 = sf::Vector2f(340, 500);
    m_allPoints.push_back(ground4);

    sf::Vector2f ground5 = sf::Vector2f(440, 575);
    m_allPoints.push_back(ground5);

    sf::Vector2f ground6 = sf::Vector2f(560, 600);
    m_allPoints.push_back(ground6);

    sf::Vector2f ground7 = sf::Vector2f(680, 600);
    m_allPoints.push_back(ground7);

    sf::Vector2f ground8 = sf::Vector2f(800, 575);
    m_allPoints.push_back(ground8);

    sf::Vector2f ground9 = sf::Vector2f(900, 475);
    m_allPoints.push_back(ground9);

    sf::Vector2f ground10 = sf::Vector2f(1200, 400);
    m_allPoints.push_back(ground10);

    //set ground points that are safe to land between (groups of 2)
    m_landingIndexes.push_back(ground3);
    m_landingIndexes.push_back(ground4);
    m_landingIndexes.push_back(ground6);
    m_landingIndexes.push_back(ground7);
}

void Ground::render(sf::RenderWindow& window) {

    //draw lines between each ground point
    for (int i = 0; i < m_allPoints.size() - 1; i++) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[i].x, m_allPoints[i].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[i + 1].x, m_allPoints[i + 1].y)),
        };
        window.draw(line, 2, sf::Lines);
    }

}