#pragma once
#include <SFML/Graphics.hpp>

class Platform {
public:
    Platform(float width = 100.f, float height = 20.f);

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void move(float offset);
    void setTexture(const sf::Texture& texture);

    const sf::Sprite& getSprite() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite sprite_;
    float width_;
    float height_;
};