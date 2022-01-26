/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>

#include "Ship.h"
#include "Ground.h"


void makeMainMenu(sf::RenderWindow& window, sf::Font font) {
    //make the main title menu

    //make title text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(120);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(200, 50));
    titleText.setString("Lunar Lander");
    window.draw(titleText);

    //make controls text
    sf::Text controlsText1;
    controlsText1.setFont(font);
    controlsText1.setCharacterSize(50);
    controlsText1.setFillColor(sf::Color::White);
    controlsText1.setPosition(sf::Vector2f(250, 400));
    controlsText1.setString("- Use Arrow keys to tilt -");
    window.draw(controlsText1);

    //make snake colour text
    sf::Text controlsText2;
    controlsText2.setFont(font);
    controlsText2.setCharacterSize(50);
    controlsText2.setFillColor(sf::Color::White);
    controlsText2.setPosition(sf::Vector2f(280, 500));
    controlsText2.setString("- Use Up or X to boost -");
    window.draw(controlsText2);

    //make start game text
    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(60);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(sf::Vector2f(150, 700));
    startText.setString("--- press Enter to start ---");
    window.draw(startText);
}

int main()
{
    //initialise window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Lunar Lander : A0050289");

    srand(time(NULL));

    Ship newShip(100, 55);
    Ground newGround;

    float gravity = 0.07;
    float maxGravity = 3;

    bool menuActive = true;

    //load font
    sf::Font font;
    if (!font.loadFromFile("Fonts\\upheavtt.ttf")) {
        return 0;
    }

    sf::Clock gameClock;
            
    //=================================================================================================================================================================

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        }

        //create game tick
        float deltaTime = gameClock.getElapsedTime().asMilliseconds();
        if (deltaTime > 20.0f) {

            //update
            newShip.update(gravity, maxGravity);

            //clear
            window.clear();

            if (newShip.getMenuActive()) {
                //make main menu if first time loading
                makeMainMenu(window, font);

            }
            else {

                //check collisions
                newShip.checkCollision(newGround.getGpoints(), newGround.getLandingIndexes());

                //draw
                newShip.render(window);
                newGround.render(window);

                //draw UI
                //================================================================================================================================================================= 

                //set text for velocity x and y
                sf::Text velocityText;
                velocityText.setFont(font);
                velocityText.setCharacterSize(25);
                velocityText.setFillColor(sf::Color::White);
                velocityText.setPosition(sf::Vector2f(970, 10));

                //round velocity to 2 dp
                std::string velocityX = std::to_string(newShip.getVelocity().x);
                velocityX = velocityX.substr(0, velocityX.find(".") + 3);
                std::string velocityY = std::to_string(-newShip.getVelocity().y);
                velocityY = velocityY.substr(0, velocityY.find(".") + 3);

                velocityText.setString("X Velocity: " + velocityX + "\nY Velocity: " + velocityY);
                window.draw(velocityText);

                //set text for boost amount
                sf::Text boostText;
                boostText.setFont(font);
                boostText.setCharacterSize(25);
                boostText.setFillColor(sf::Color::White);
                boostText.setPosition(sf::Vector2f(970, 55));
                boostText.setString("Fuel: " + std::to_string(newShip.getBoostAmount()));
                window.draw(boostText);

                //set text for win/lose
                sf::Text endText;
                endText.setFont(font);
                endText.setCharacterSize(75);
                endText.setFillColor(sf::Color::White);
                endText.setPosition(sf::Vector2f(450, 100));

                //set text for restart
                sf::Text retryText;
                retryText.setFont(font);
                retryText.setCharacterSize(40);
                retryText.setFillColor(sf::Color::White);
                retryText.setPosition(sf::Vector2f(300, 200));
                retryText.setString("--- Press SPACE to Replay ---");

                if (newShip.getExploded()) {
                    //lose game if ship exploades
                    endText.setString("YOU LOSE");
                }
                else if (newShip.getLanded() && !newShip.getExploded()) {
                    //if ship doesnt expload, it has landed safely
                    endText.setString("YOU WIN");
                }

                if (newShip.getLanded()) {
                    window.draw(endText);
                    window.draw(retryText);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        //reset game
                        newShip.reset();
                    }

                }
            }

            //display
            window.display();

            gameClock.restart();
        }
        
    }

    return 0;
}
