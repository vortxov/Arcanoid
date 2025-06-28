#pragma once
#include "SFML/System/Vector2.hpp"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr float BOTTOM_DEAD_ZONE = 30.f;

constexpr int BONUS_DROP_CHANCE_PERCENT = 100;	// 1 = 1% шанс выпадения бонуса // Release: value = 20;
constexpr int SPAWN_BRICK_STRONG_PERCENT = 10;	// 1 = 1% шанс появления на карте этого типа кирпича
constexpr int SPAWN_BRICK_GLASS_PERCENT = 25;	// 1 = 1% шанс появления на карте этого типа кирпича

constexpr float BONUS_FALLING_SPEED = 100.f;
constexpr float BONUS_ACTIVITY_DURATION = 3.f;	// In seconds

constexpr float BALL_RADIUS = 10.f;
constexpr float BALL_SPEED = 250.f;
constexpr float FIREBALL_MULTIPLIER_SPEED = 1.5f;
constexpr float MIN_CORRECTION_ANGLE = 10.0f;  // Минимальный угол от вертикали
constexpr float MAX_CORRECTION_ANGLE = 15.0f;  // Максимальный угол от вертикали
const sf::Vector2f BALL_START_POSITION = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 150.f };

constexpr float PLATFORM_SPEED = 300.0f;
constexpr float PLATFORM_WITH_BONUS_SPEED = 500.0f;
const sf::Vector2f PLATFORM_SIZE = { 100.f, 20.f };
const sf::Vector2f PLATFORM_WITH_BONUS_SIZE = { 170.f, 20.f };
