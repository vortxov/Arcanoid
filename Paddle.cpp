#include "Paddle.h"

#include "Paddle.h"

Paddle::Paddle(float x, float y, float width, float height, sf::Color color) {
    shape_.setPosition(x, y);
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(color);
}

void Paddle::setPosition(float x, float y) 
{
    position_.x = x;
    position_.y = y;
    shape_.setPosition(position_);
}

sf::Vector2f Paddle::getPosition() const 
{
    return position_;
}

void Paddle::move(float offset) 
{
    position_.x += offset;
    shape_.setPosition(position_);
}

const sf::RectangleShape& Paddle::getShape() const 
{
    return shape_;
}

sf::FloatRect Paddle::getGlobalBounds() const 
{
    return shape_.getGlobalBounds();
}