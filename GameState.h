#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Platform.h"
#include "Ball.h"
#include "StrongBrick.h"
#include "ScoreSystem.h"
#include "TextureManager.h"
#include "Bonus.h"
#include "Constants.h"

class GameState
{
public:
	GameState(unsigned int width, unsigned int height);	 // Конструктор, инициализирует состояние игры
	void run();											 // Главный игровой цикл

private:
	// Инициализация и настройка
	void initialize();					 // Общая инициализация игры
	void setupWindow();					 // Настройка окна
	void loadResources();				 // Загрузка текстур и шрифтов
	void initGameObjects();				 // Создание и размещение игровых объектов
	void setupText();					 // Настройка текста (экран победы/поражения)
	void centerText(sf::Text& text);	 // Центрирование текста на экране
	void setupScoreDisplay();			 // Подготовка отображения счета
	void updateScoreDisplay(int score);	 // Обновление текста счета и рекордов

	// Игровой процесс
	std::vector<std::unique_ptr<Block>> bricks_;  // Кирпичи на поле

	void handleEvents();						  // Обработка событий SFML
	void update(float deltaTime);				  // Обновление состояния игры
	void render();								  // Отрисовка всех объектов
	void handleInput();							  // Управление платформой с клавиатуры
	void clampPlatformPosition();				  // Ограничение движения платформы в пределах экрана
	void updateBall(float deltaTime);			  // Обновление мяча
	void updateBallSpeed(float deltaTime);		  // Постепенное ускорение мяча
	void initBricks();							  // Создание кирпичей на поле
	void pushBonus(Block& brick);				  // Создание бонуса после разрушения кирпича

	// Проверка коллизий
	void checkCollisions();									// Проверка всех столкновений
	void checkWallCollisions();								// Проверка столкновений мяча со стенами
	void checkPlatformCollision();							// Проверка столкновения мяча с платформой
	void checkBrickCollisions();							// Проверка столкновения мяча с кирпичами
	void handleBrickCollisionResponse(const Block& brick);	// Реакция на столкновение с кирпичом

	// Проверка условий завершения игры
	void checkGameConditions();	 // Проверка победы или поражения
	void checkLoseCondition();	 // Проверка условия проигрыша
	void checkWinCondition();	 // Проверка условия победы

	// Экран победы/поражения
	void showWinScreen();		   // Отображение экрана победы
	void handleWinScreenInput();   // Обработка ввода на экране победы
	void showLoseScreen();		   // Отображение экрана поражения
	void handleLoseScreenInput();  // Обработка ввода на экране поражения
	void resetGame();			   // Сброс состояния игры

	// Ресурсы и текстуры
	static TextureManager textureManager;  // Глобальный менеджер текстур
	ScoreSystem scoreSystem_;			   // Система подсчета очков
	sf::Text scoreText_;				   // Отображение текущего счета
	sf::Text highscoreText_;			   // Отображение рекордов
	sf::Font font_;						   // Шрифт
	sf::Text winText_;					   // Текст победы
	sf::Text loseText_;					   // Текст поражения
	sf::Sprite background_;				   // Фон

	// Игровые объекты
	std::unique_ptr<sf::RenderWindow> window_;	  // Окно SFML
	std::unique_ptr<Platform> platform_;		  // Платформа
	std::unique_ptr<Ball> ball_;				  // Мяч
	std::vector<std::unique_ptr<Block>> blocks_;  // Кирпичи (возможно, устарело — уже есть `bricks_`)
	std::vector<Bonus> bonuses_;				  // Активные бонусы на поле

	// Состояние игры
	bool gameWon_;	 // Флаг победы
	bool gameLost_;	 // Флаг поражения
	bool onMenu_;	 // Находится ли игрок в меню

	// Параметры платформы и мяча
	const float platformSpeed_ = 5.0f;			  // Скорость платформы
	float currentBallSpeedMultiplier_;			  // Текущий множитель скорости мяча
	float ballSpeedChangeTimer_;				  // Таймер для ускорения мяча
	const float ballSpeedChangeInterval_ = 1.0f;  // Интервал ускорения
	const float minBallSpeedMultiplier_ = 1.0f;	  // Минимальный множитель
	const float maxBallSpeedMultiplier_ = 1.5f;	  // Максимальный множитель
};