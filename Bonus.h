#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

enum class BonusType { BrittleBrick, FireBall, BoostPlatformSpeed, None };
class Bonus
{
protected:
	BonusType bonusType = BonusType::None;
	
	sf::Texture texture;

public:
	sf::Sprite sprite_;
	void SetRandomBonusType(int randomBonusType);
	BonusType GetBonusType() { return bonusType;  };

	void draw(sf::RenderWindow window);

	void initBonus(const sf::Vector2f& brickPosition);
};

