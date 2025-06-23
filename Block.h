#pragma once
#include <SFML/Graphics.hpp>
#include "Bonus.h"

enum class EBT_BrickType
{
	EBT_Normal,
	EBT_Glass,
	EBT_Strong,
	EBT_None
};

class Block
{
public:
	Block(int blowsToDestroy, bool shouldBallBounce);
	~Block() = default;

	void SetRandomBonus(int random_number);
	Bonus& GetBonus() { return bonus; };

	void hit();
	bool isDestroyed() const;
	void setPosition(float x, float y);
	void setTexture(const sf::Texture& texture);
	bool getShouldBallBounce() const { return shouldBallBounce_; }

	sf::Sprite getSprite() { return sprite_; };

	void draw(sf::RenderWindow& window) const;
	sf::FloatRect getGlobalBounds() const;

	void setCurrentBrickType(EBT_BrickType brickType) { currentBrickType_ = brickType; }
	EBT_BrickType getCurrentBrickType() const { return currentBrickType_; }
	EBT_BrickType getPastBrickType() const { return pastBrickType_; }

private:
	bool destroyed_;
	bool shouldBallBounce_;
	int hitPoints_;

	sf::Sprite sprite_;
	Bonus bonus;

	EBT_BrickType currentBrickType_ = EBT_BrickType::EBT_None;
	EBT_BrickType pastBrickType_ = EBT_BrickType::EBT_None;
};