#include "BallPlayer.h"

BallPlayer::BallPlayer(float length, sf::Vector2f startPosition, Texture* texture, float initialSpeed, CellGrid* myCellGrid, float* dt, std::vector<sf::FloatRect*> allboundries)
    : speed(initialSpeed), position(startPosition), dt(dt), myCellGrid(myCellGrid), allboundries(allboundries) {
    isUp = false;
    shape.setSize(sf::Vector2f(length, length));
    this->animation = new Animation(texture, Vector2u(3, 2), 0.3f);
    shape.setPosition(startPosition);
    shape.setTexture(texture);
    shape.setTextureRect(animation->texRec);

}

void BallPlayer::move(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) {
    velocity.x = 0.f;
    velocity.y = 0.f;
    if (sf::Keyboard::isKeyPressed(leftKey)) {
        isUp = false;
        velocity.x -= speed * (*dt);
        animation->update(0, *dt);
        shape.setTextureRect(animation->texRec);
    }
    if (sf::Keyboard::isKeyPressed(rightKey)) {
        isUp = false;
        velocity.x += speed * (*dt);
        animation->update(0, *dt);
        shape.setTextureRect(animation->texRec);
    }
    if (sf::Keyboard::isKeyPressed(upKey)) {
        isUp = true;
        velocity.y -= speed * (*dt);
        animation->update(0, *dt);
        shape.setTextureRect(animation->texRec);
    }
    if (sf::Keyboard::isKeyPressed(downKey)) {
        isUp = false;
        velocity.y += speed * (*dt);
        animation->update(0, *dt);
        shape.setTextureRect(animation->texRec);
    }

    handleCollisions();
    shape.move(velocity);
}

void BallPlayer::moveWithJoystick(unsigned int joystickIndex, sf::Joystick::Axis xAxis, sf::Joystick::Axis yAxis) {
    velocity.x = 0.f;
    velocity.y = 0.f;
    if (sf::Joystick::isConnected(joystickIndex)) {
        float joystickX = sf::Joystick::getAxisPosition(joystickIndex, xAxis);
        float joystickY = sf::Joystick::getAxisPosition(joystickIndex, yAxis);

        velocity.x += ((joystickX * speed) / 100);
        velocity.y += ((joystickY * speed) / 100);

        handleCollisions();
        shape.move(velocity);
    }
}

void BallPlayer::handleCollisions() {
    for (auto wall : allboundries) {
        sf::FloatRect playerBounds = shape.getGlobalBounds();

        nextpos = &playerBounds;
        nextpos->left += velocity.x;
        nextpos->top += velocity.y;

        if (wall->intersects(*nextpos)) {
            velocity.x = 0.f;
            velocity.y = 0.f;
        }
    }
}

RectangleShape BallPlayer::getShap()
{
    return this->shape;
}

void BallPlayer::setShap(Vector2f currentPosition)
{
    this->shape.setPosition(currentPosition);
}

sf::RectangleShape BallPlayer::getShape() const {
    return shape;
}


