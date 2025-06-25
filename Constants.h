#pragma once
#include "SFML/System/Vector2.hpp"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr int BONUS_DROP_CHANCE_PERCENT = 100;	// 1 = 1% шанс выпадения бонуса
constexpr int SPAWN_BRICK_STRONG_PERCENT = 10;	// 1 = 1% шанс появления на карте этого типа кирпича
constexpr int SPAWN_BRICK_GLASS_PERCENT = 25;	// 1 = 1% шанс появления на карте этого типа кирпича

constexpr float BALL_SPEED = 1.f;
constexpr float FIREBALL_SPEED = 1.5f;
constexpr float BONUS_FALLING_SPEED = 100.f;
constexpr float BONUS_ACTIVITY_DURATION = 3.f;	// In seconds

constexpr float PLATFORM_SPEED = 300.0f;
constexpr float PLATFORM_WITH_BONUS_SPEED = 500.0f;
const sf::Vector2f PLATFORM_SIZE = { 100.f, 20.f };
const sf::Vector2f PLATFORM_WITH_BONUS_SIZE = { 170.f, 20.f };