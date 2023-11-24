#pragma once
#include <SFML/Graphics.hpp>
#include "CellGrid.h"
#include "Animation.h"

using namespace std;
using namespace sf;
class BallPlayer {
private:
    sf::Vector2f position;
    float speed;
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float* dt;
    sf::FloatRect* nextpos;
    CellGrid* myCellGrid;
    std::vector<sf::FloatRect*> allboundries;
    Animation *animation;
    

public:
    BallPlayer(float radius, sf::Vector2f startPosition, Texture* texture, float initialSpeed, CellGrid* myCellGrid, float* dt, std::vector<sf::FloatRect*> allboundries);

    void move(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);

    void moveWithJoystick(unsigned int joystickIndex, sf::Joystick::Axis xAxis, sf::Joystick::Axis yAxis);

    void handleCollisions();

    RectangleShape getShap();
    void setShap(Vector2f);
   
    sf::RectangleShape getShape() const;

    bool isUp;
};

