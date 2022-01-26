#include "Ship.h"

#include <iostream>

Ship::Ship(float x, float y) :
    m_velocity(sf::Vector2f(3, 0)),
    m_angle(2),
    m_totalAngle(0),
    m_maxSpeed(3),
    m_acceleration(0.1),
    m_boostAmount(500),
    m_boosterActive(false),
    m_landed(false),
    m_landRotate(2),
    m_exploaded(false),
    m_startX(x),
    m_startY(y)
{
    //index 0
    sf::Vector2f P0 = sf::Vector2f(m_startX, m_startY);
    m_allPoints.push_back(P0);

    //index 1
    sf::Vector2f P1 = sf::Vector2f(m_startX, m_startY - 1);
    m_allPoints.push_back(P1);

    //index 2
    sf::Vector2f TriLeft = sf::Vector2f(m_startX - 15, m_startY);
    m_allPoints.push_back(TriLeft);

    //index 3
    sf::Vector2f TriTop = sf::Vector2f(m_startX, m_startY - 30);
    m_allPoints.push_back(TriTop);

    //index 4
    sf::Vector2f TriRight = sf::Vector2f(m_startX + 15, m_startY);
    m_allPoints.push_back(TriRight);

    //index 5
    sf::Vector2f Boost1 = sf::Vector2f(m_startX - 5, m_startY);
    m_allPoints.push_back(Boost1);

    //index 6
    sf::Vector2f Boost2 = sf::Vector2f(m_startX, m_startY + 8);
    m_allPoints.push_back(Boost2);

    //index 7
    sf::Vector2f Boost3 = sf::Vector2f(m_startX + 5, m_startY);
    m_allPoints.push_back(Boost3);

    //index 8
    sf::Vector2f exploadedLeft = m_allPoints[2];
    m_allPoints.push_back(exploadedLeft);

    //index 9
    sf::Vector2f exploadedTop = m_allPoints[3];
    m_allPoints.push_back(exploadedTop);

    //index 10
    sf::Vector2f exploadedRight = m_allPoints[4];
    m_allPoints.push_back(exploadedRight);

    //randomise velocity for exploded peices
    m_leftVelocity = sf::Vector2f((rand() % 4) - 2, (rand() % 2) - 4);
    m_topVelocity = sf::Vector2f((rand() % 4) - 2, (rand() % 2) - 4);
    m_rightVelocity = sf::Vector2f((rand() % 4) - 2, (rand() % 2) - 4);

}

sf::Vector2f Ship::rotatePoint(sf::Vector2f pointA, sf::Vector2f pointB, float angle) {
    //rotate a point about another arbitary point
    float tempPointX = pointB.x - pointA.x;
    float tempPointY = pointB.y - pointA.y;

    float cosAngle = cos((angle * M_PI) / 180);
    float sinAngle = sin((angle * M_PI) / 180);

    float newX = (tempPointX * cosAngle) - (tempPointY * sinAngle);
    float newY = (tempPointX * sinAngle) + (tempPointY * cosAngle);

    pointB.x = newX + pointA.x;
    pointB.y = newY + pointA.y;

    return pointB;
}

float Ship::getLength(sf::Vector2f ground1, sf::Vector2f ground2) {
    //calculate the distance between 2 points (modulus of the vector between them)
    float lengthVectorX = ground2.x - ground1.x;
    float lengthVectorY = ground2.y - ground1.y;

    return sqrt(pow(lengthVectorX, 2) + pow(lengthVectorY, 2));
}

void Ship::update(float gravity, float maxGravity) {
    if (m_menuActive) {
        //get start menu input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            m_menuActive = false;
        }
    }
    else if (!m_menuActive) {
        //if the game has started, and the game hasnt been won or lost:
        if (!(m_exploaded || m_landed)) {
            //get player input for tilting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                m_totalAngle += m_angle;
                //locks angle to 90 degrees clockwise
                if (m_totalAngle > 90 && m_totalAngle < 269) {
                    m_totalAngle = 90;
                }
                if (m_totalAngle >= 360) {
                    m_totalAngle = 0;
                }
                if ((m_totalAngle >= 0 && m_totalAngle < 90) || (m_totalAngle > 269 && m_totalAngle <= 359)) {
                    for (int i = 1; i < m_allPoints.size(); i++) {
                        m_allPoints[i] = rotatePoint(m_allPoints[0], m_allPoints[i], m_angle);
                    }
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                m_totalAngle -= m_angle;
                //locks angle to 90 degrees anti-clockwise
                if (m_totalAngle > 90 && m_totalAngle < 269) {
                    m_totalAngle = 269;
                }
                if (m_totalAngle <= -1) {
                    m_totalAngle = 359;
                }
                if ((m_totalAngle >= 0 && m_totalAngle < 90) || (m_totalAngle > 269 && m_totalAngle <= 359)) {
                    for (int i = 1; i < m_allPoints.size(); i++) {
                        m_allPoints[i] = rotatePoint(m_allPoints[0], m_allPoints[i], -m_angle);
                    }
                }
            }

            //get boost input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                m_boosterActive = true;
                m_boostAmount--;

                //player runs out of boost
                if (m_boostAmount < 0) {
                    m_boostAmount = 0;
                    m_boosterActive = false;
                }
            }
            else {
                m_boosterActive = false;
            }

            //update velocity
            if (m_boosterActive) {
                //update X Velocity
                //calculate velocity based on unit vector of direction
                m_velocity.x += m_acceleration * (m_allPoints[1].x - m_allPoints[0].x);
                if (m_velocity.x > m_maxSpeed) {
                    m_velocity.x = m_maxSpeed;
                }
                else if (m_velocity.x < -m_maxSpeed) {
                    m_velocity.x = -m_maxSpeed;
                }

                //update Y Velocity
                //calculate velocity based on unit vector of direction
                m_velocity.y += m_acceleration * (m_allPoints[1].y - m_allPoints[0].y);
                if (m_velocity.y > m_maxSpeed) {
                    m_velocity.y = m_maxSpeed;
                }
                else if (m_velocity.y < -m_maxSpeed) {
                    m_velocity.y = -m_maxSpeed;
                }

            }

            //add gravity to y velocity
            m_velocity.y += gravity;
            if (m_velocity.y > maxGravity) {
                m_velocity.y = maxGravity;
            }

            //add velocity to all points
            for (auto& point : m_allPoints) {
                point.x += m_velocity.x;
                point.y += m_velocity.y;
            }

            //update duplicate points (used for explosion)
            m_allPoints[8] = m_allPoints[2];
            m_allPoints[9] = m_allPoints[3];
            m_allPoints[10] = m_allPoints[4];
        }
        else if (m_exploaded) {

            //add pre randomised velocies to all points (making the ship explode)
            m_allPoints[9] += m_leftVelocity;
            m_allPoints[8] += m_rightVelocity;
            m_allPoints[10] += m_topVelocity;

            m_allPoints[2] += m_leftVelocity;
            m_allPoints[3] += m_topVelocity;
            m_allPoints[4] += m_rightVelocity;

        }
    }
}

void Ship::checkCollision(std::vector<sf::Vector2f> groundPoints, std::vector<sf::Vector2f> landingIndexes) {
    bool safeZone = false;

    //check all ground points
    for (size_t i = 0; i < groundPoints.size() - 1; i++) {
        for (size_t j = 0; j < landingIndexes.size() - 1; j++) {
            //if the 2 adjacent points are in the landingIndexes vector, it is a safe point to land on
            if (groundPoints[i] == landingIndexes[j] && groundPoints[i + 1] == landingIndexes[j + 1]) {
                safeZone = true;
                break;
            }
            else {
                safeZone = false;
            }
        }

        //compare the length of each ground point to the ship, to the length of the ground segment,
        //if the are close to equal, ship has landed
        float lengthAB = getLength(groundPoints[i], groundPoints[i + 1]);

        //check collisions on left ship corner
        float lengthAC = getLength(groundPoints[i], m_allPoints[2]);
        float lengthCB = getLength(m_allPoints[2], groundPoints[i + 1]);

        float leftLength = lengthAC + lengthCB;

        if (leftLength < lengthAB + 0.02) {
            m_boosterActive = false;
            m_landed = true;

            if (safeZone && m_velocity.y < 1.5 && m_velocity.x < 1) {
                //if safe landing, land
                if (m_allPoints[4].y < groundPoints[i].y) {
                    //rotate ship to ground
                    m_allPoints[0] = rotatePoint(m_allPoints[2], m_allPoints[0], m_landRotate);
                    m_allPoints[1] = rotatePoint(m_allPoints[2], m_allPoints[1], m_landRotate);
                    m_allPoints[3] = rotatePoint(m_allPoints[2], m_allPoints[3], m_landRotate);
                    m_allPoints[4] = rotatePoint(m_allPoints[2], m_allPoints[4], m_landRotate);
                }

            }
            else if (!safeZone || m_velocity.y >= 1.5 || m_velocity.x >= 1) {
                //else expload
                m_exploaded = true;
            }

            

        }

        //check collisions on right
        lengthAC = getLength(groundPoints[i], m_allPoints[4]);
        lengthCB = getLength(m_allPoints[4], groundPoints[i + 1]);

        float rightLength = lengthAC + lengthCB;

        if (rightLength < lengthAB + 0.02) {
            m_boosterActive = false;
            m_landed = true;

            if (safeZone && m_velocity.y < 1.5 && m_velocity.x < 1) {
                //if safe landing, land
                if (m_allPoints[2].y < groundPoints[i].y) {
                    //rotate to ground
                    m_allPoints[0] = rotatePoint(m_allPoints[4], m_allPoints[0], -m_landRotate);
                    m_allPoints[1] = rotatePoint(m_allPoints[4], m_allPoints[1], -m_landRotate);
                    m_allPoints[2] = rotatePoint(m_allPoints[4], m_allPoints[2], -m_landRotate);
                    m_allPoints[3] = rotatePoint(m_allPoints[4], m_allPoints[3], -m_landRotate);
                }

            }
            else if (!safeZone || (m_velocity.y >= 1.5 || m_velocity.x >= 1)) {
                //else expload
                m_exploaded = true;
            }
        }

    }
   
}

void Ship::render(sf::RenderWindow& window) {
    //render all ship points
    if (!m_exploaded) {

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[2].x, m_allPoints[2].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[3].x, m_allPoints[3].y)),
        };
        window.draw(line, 2, sf::Lines);

        sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[3].x, m_allPoints[3].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[4].x, m_allPoints[4].y)),
        };
        window.draw(line2, 2, sf::Lines);

        sf::Vertex line3[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[4].x, m_allPoints[4].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[2].x, m_allPoints[2].y)),
        };
        window.draw(line3, 2, sf::Lines);
    }
    else {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[2].x, m_allPoints[2].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[9].x, m_allPoints[9].y)),
        };
        window.draw(line, 2, sf::Lines);

        sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[3].x, m_allPoints[3].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[10].x, m_allPoints[10].y)),
        };
        window.draw(line2, 2, sf::Lines);

        sf::Vertex line3[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[4].x, m_allPoints[4].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[8].x, m_allPoints[8].y)),
        };
        window.draw(line3, 2, sf::Lines);
    }


    //render booster
    if (m_boosterActive) {
        sf::Vertex line4[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[5].x, m_allPoints[5].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[6].x, m_allPoints[6].y)),
        };
        window.draw(line4, 2, sf::Lines);

        sf::Vertex line5[] =
        {
            sf::Vertex(sf::Vector2f(m_allPoints[6].x, m_allPoints[6].y)),
            sf::Vertex(sf::Vector2f(m_allPoints[7].x, m_allPoints[7].y)),
        };
        window.draw(line5, 2, sf::Lines);
    }
}

void Ship::reset() {
    //reset game variables
    m_velocity = sf::Vector2f(3, 0);
    m_angle = 2;
    m_totalAngle = 0;
    m_boostAmount = 500;
    m_boosterActive = false;
    m_landed = false;
    m_landRotate = 2;
    m_exploaded = false;
    //m_menuActive = true;

    //reset all ship positions
    m_allPoints[0] = sf::Vector2f(m_startX, m_startY);
    m_allPoints[1] = sf::Vector2f(m_startX, m_startY - 1);
    m_allPoints[2] = sf::Vector2f(m_startX - 15, m_startY);
    m_allPoints[3] = sf::Vector2f(m_startX, m_startY - 30);
    m_allPoints[4] = sf::Vector2f(m_startX + 15, m_startY);
    m_allPoints[5] = sf::Vector2f(m_startX - 5, m_startY);
    m_allPoints[6] = sf::Vector2f(m_startX, m_startY + 8);
    m_allPoints[7] = sf::Vector2f(m_startX + 5, m_startY);
    m_allPoints[8] = m_allPoints[2];
    m_allPoints[9] = m_allPoints[3];
    m_allPoints[10] = m_allPoints[4];

    //re randomise velocities of explosion
    m_leftVelocity = sf::Vector2f((rand() % 4) - 2, (rand() % 2) - 4);
    m_topVelocity = sf::Vector2f((rand() % 4) - 2, (rand() % 2) - 4);
    m_rightVelocity = sf::Vector2f((rand() % 4) - 2, (rand() % 2) - 4);
}