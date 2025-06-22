#include "Platform.h"

Platform::Platform(float width, float height) :
    width_(width),
    height_(height) {}

void Platform::setPosition(float x, float y) {
    sprite_.setPosition(x, y);
}

sf::Vector2f Platform::getPosition() const {
    return sprite_.getPosition();
}

void Platform::move(float offset) {
    sprite_.move(offset, 0);
}

void Platform::setTexture(const sf::Texture& texture) {
    sprite_.setTexture(texture);
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setScale(width_ / bounds.width, height_ / bounds.height);
    sprite_.setColor(sf::Color::White);
}

const sf::Sprite& Platform::getSprite() const {
    return sprite_;
}

sf::FloatRect Platform::getGlobalBounds() const {
    return sprite_.getGlobalBounds();
}