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
	void setPosition(float x, float y);
	void setTexture(const sf::Texture& texture);
	void setCurrentBrickType(EBT_BrickType brickType);
	void updateState(TextureManager& textureManager);
	void draw(sf::RenderWindow& window) const;

	bool isDestroyed() const { return destroyed_; }
	bool getShouldBallBounce() const { return shouldBallBounce_; }
	sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }
	sf::Sprite getSprite() { return sprite_; };

	EBT_BrickType getCurrentBrickType() const { return currentBrickType_; }
	EBT_BrickType getPastBrickType() const { return pastBrickType_; }

private:
	bool destroyed_;
	bool shouldBallBounce_;
	int hitPoints_;

	sf::Sprite sprite_;
	Bonus bonus;

	EBT_BrickType currentBrickType_ = EBT_BrickType::EBT_Normal;
	EBT_BrickType pastBrickType_ = EBT_BrickType::EBT_None;
};