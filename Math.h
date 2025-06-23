#pragma once
#include <memory>

class Platform;
class Ball;
class Block;

namespace Math
{
	template <typename T>
	const T& clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	// === Коллизии ===
	// void checkCollisions();																						  // Общая проверка всех коллизий
	void checkWallCollisions(const std::unique_ptr<Ball>& ball);												// Коллизия мяча со стенами
	void checkPlatformCollision(const std::unique_ptr<Platform>& platform, const std::unique_ptr<Ball>& ball);	// Коллизия мяча с платформой
	bool isBrickHitByBall(const std::unique_ptr<Block>& brick, const std::unique_ptr<Ball>& ball);				// Коллизия мяча с кирпичами
	void handleBrickCollisionResponse(const Block& brick, const std::unique_ptr<Ball>& ball);					// Ответная реакция на столкновение с кирпичом

																												// void checkBonusWithPlatformCollision();					// Коллизия бонусов с платформой
}  // namespace Math
