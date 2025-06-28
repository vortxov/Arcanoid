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

class Brick
{
public:
	Brick(int blowsToDestroy = 1, bool shouldBallBounce = true);
	~Brick() = default;

	void SetRandomBonus(int random_number);
	Bonus& GetBonus() { return bonus; };

	void hit();
	void setPosition(float x, float y);
	void setTexture(const sf::Texture& texture);
	void setCurrentBrickType(EBT_BrickType brickType, bool savePastBrickType = true);
	void setPastBrickType(EBT_BrickType brickType);
	void applyBrittle();
	void updateState(TextureManager& textureManager);
	void draw(sf::RenderWindow& window) const;
	void SetIsDestroyed(bool isDestroyed) { destroyed_ = isDestroyed; };

	bool isDestroyed() const { return destroyed_; }
	bool getShouldBallBounce() const { return shouldBallBounce_; }
	sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }
	sf::Sprite getSprite() { return sprite_; };
	int getHitPoints() {return hitPoints_; };

	EBT_BrickType getCurrentBrickType() const { return currentBrickType_; }
	EBT_BrickType getPastBrickType() const { return pastBrickType_; }

private:
	bool destroyed_;
	bool shouldBallBounce_;
	int hitPoints_;

	sf::Sprite sprite_;
	Bonus bonus;

	EBT_BrickType currentBrickType_;
	EBT_BrickType pastBrickType_;
};