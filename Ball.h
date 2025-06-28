#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball(float radius);

	void setPosition(float x, float y);
	void setVelocity(const sf::Vector2f& velocity);
	void setSpeedMultiplier(float multiplier);
	void setTexture(const sf::Texture& texture);

	void update(float deltaTime);
	void reset(float x, float y);
	void reverseX();
	void reverseY();

	void adjustTrajectoryIfNeeded();
	void incrementWallCollisionCount() { ++wallCollisionCount_; }
	void resetWallCollisionCount() { wallCollisionCount_ = 0; }
	int getWallCollisionCount() const { return wallCollisionCount_; }
	float getRadius() const { return radius_; }
	float getSpeedMultiplier() const { return speedMultiplier_; }

	sf::Sprite& getSprite() { return sprite_; }
	sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }
	sf::Vector2f getPosition() const { return sprite_.getPosition(); }
	sf::Vector2f getVelocity() const { return velocity_ * speedMultiplier_; }
	sf::Vector2f getRandomBallDirection(bool canGoUp = true);
	sf::Vector2f getRandomBallDirection(float minAngle, float maxAngle, bool canGoUp = false);

private:
	float radius_;
	float speedMultiplier_;
	int wallCollisionCount_;
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	sf::Sprite sprite_;
};