#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"

class Paddle : public GameObject {
public:
    Paddle(float x, float y, float width, float height, sf::Color color);
    void Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window) override;
    void HandleInput(sf::Event& event);
    sf::FloatRect GetBounds() const;

private:
    sf::Vector2f position_;
    sf::Vector2f size_;
    sf::RectangleShape shape_;
};
#endif