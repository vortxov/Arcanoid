#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball(float radius = 10.f);

	void setPosition(float x, float y);
	void setVelocity(const sf::Vector2f& velocity);
	void setSpeedMultiplier(float multiplier);
	void setTexture(const sf::Texture& texture);

	void update(float deltaTime);
	void reset(float x, float y);
	void reverseX();
	void reverseY();

	const sf::Sprite& getSprite() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	float getRadius() const;
	float getSpeedMultiplier() const;  // Not used

private:
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	float speedMultiplier_;
	sf::Sprite sprite_;
	float radius_;
};