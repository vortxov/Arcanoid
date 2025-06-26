#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
public:
	Platform(const sf::Vector2f& platformSize);

	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;
	void move(float offset);
	void setTexture(const sf::Texture& texture);
	void setSize(const sf::Vector2f& newSize);
	void setSpeed(float newSpeed) { platformSpeed_ = newSpeed; }
	void update(float deltaTime);

	const sf::Sprite& getSprite() const;
	sf::FloatRect getGlobalBounds() const;

private:
	bool isResizing_ = false;
	float platformSpeed_ = 0.0f;
	float resizeTimer_ = 0.0f;	   // Таймер
	float resizeDuration_ = 0.5f;  // Длительность изменения
	sf::Vector2f platformSize_;	   // Текущий размер
	sf::Vector2f startSize_;	   // Начальный размер
	sf::Vector2f targetSize_;	   // Целевой размер
	sf::Sprite sprite_;
};