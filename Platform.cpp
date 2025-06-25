#include "Platform.h"

#include "Constants.h"

Platform::Platform(const sf::Vector2f& platformSize)
{
	platformSize_ = platformSize;
	platformSpeed_ = PLATFORM_SPEED;
}

void Platform::setPosition(float x, float y)
{
	sprite_.setPosition(x, y);
}

sf::Vector2f Platform::getPosition() const
{
	return sprite_.getPosition();
}

void Platform::move(float offset)
{
	sf::FloatRect bounds = sprite_.getLocalBounds();
	sprite_.setScale(platformSize_.x / bounds.width, platformSize_.y / bounds.height);
	sprite_.move(offset * platformSpeed_, 0);
}

void Platform::setTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
}

void Platform::setSize(const sf::Vector2f& newSize)
{
	startSize_ = platformSize_;
	targetSize_ = newSize;
	resizeTimer_ = 0.0f;
	isResizing_ = true;
}

void Platform::update(float deltaTime)
{
	// Если платформа в процессе изменения размера
	if (isResizing_)
	{
		resizeTimer_ += deltaTime;

		// Вычисляем, насколько анимация продвинулась от 0.0 до 1.0
		// 0.0 — только началось, 1.0 — завершено
		float progressRatio = std::min(resizeTimer_ / resizeDuration_, 1.0f);
		platformSize_ = startSize_ + progressRatio * (targetSize_ - startSize_);

		sf::FloatRect bounds = sprite_.getLocalBounds();
		sprite_.setScale(platformSize_.x / bounds.width, platformSize_.y / bounds.height);

		// Если анимация завершена (progressRatio достиг 1.0), останавливаем процесс изменения
		if (progressRatio >= 1.0f)
		{
			isResizing_ = false;
		}
	}
}

const sf::Sprite& Platform::getSprite() const
{
	return sprite_;
}

sf::FloatRect Platform::getGlobalBounds() const
{
	return sprite_.getGlobalBounds();
}