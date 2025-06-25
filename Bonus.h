#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Platform;

enum class BonusType
{
	BrittleBrick,
	FireBall,
	BoostPlatformSpeed,
	None
};

class Bonus
{
public:
	void initBonus(const sf::Vector2f& brickPosition);
	void update(float deltaTime);
	void SetRandomBonusType(int randomBonusType);
	bool checkBonusWithPlatformCollision(const std::unique_ptr<Platform>& platform) const;
	void draw(sf::RenderWindow window);

	sf::Sprite getSprite() const { return sprite_; }
	sf::Clock GetBonusDurationTimer() const { return bonusDurationTimer; }
	sf::FloatRect getBounds() const;
	BonusType GetBonusType() const { return bonusType; };

private:
	sf::Sprite sprite_;
	sf::Texture texture;
	sf::Clock bonusDurationTimer;
	BonusType bonusType = BonusType::None;
};
