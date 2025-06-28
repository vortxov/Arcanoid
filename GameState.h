#pragma once
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include "ScoreSystem.h"
#include "TextureManager.h"
#include "Bonus.h"
#include "MenuState.h"
#include "Constants.h"
#include "SaveSystem.h"


enum class StateScreen  // Состояние экрана
{
	Game,
	Menu,
	Records,
	GameWon,
	GameLost
};

class GameState
{
public:
	GameState();  // Конструктор
	void run();	  // Запуск главного игрового цикла

private:
	// === Инициализация и настройки ===
	void initialize();						// Общая инициализация игры
	void setupWindow();						// Настройка окна SFML
	void loadResources();					// Загрузка текстур, шрифтов и т.п.
	void initGameObjects();					// Создание объектов: платформа, мяч, кирпичи
	void setupText();						// Настройка текста (очки, победа, поражение)
	void centerText(sf::Text& text) const;	// Центрирование текста по экрану
	void setupScoreDisplay();				// Настройка отображения очков
	void updateScoreDisplay(int score);		// Обновление текста счёта

	// === Игровая логика ===
	std::vector<std::unique_ptr<Brick>> bricks_;  // Все кирпичи на сцене

	void handleEvents();						  // Обработка событий (ввод, закрытие)
	void update(float deltaTime);				  // Обновление логики игры
	void render();								  // Отрисовка кадра
	void handleInput(float deltaTime);			  // Обработка клавиш
	void clampPlatformPosition();				  // Ограничение движения платформы
	void updateBall(float deltaTime);			  // Обновление позиции мяча
	// void AccelerationBallSpeed(float deltaTime);  // Управление изменением скорости мяча // Not used
	void initBricks();							  // Создание и размещение кирпичей
	void pushBonus(Brick& brick);				  // Добавление бонуса при разрушении кирпича
	void updateBonus(float deltaTime);			  // Обновление положения и состояния бонусов
	void applyBonusEffect(BonusType bonusType);	  //
	void cancelBonusEffect(BonusType bonusType);  //
	void clearActiveBonuses();					  // Очистка бонусов, которые уже достигли платформы
	void clearBonus();							  // Очистка всех активных бонусов

	// === Проверка условий завершения игры ===
	void checkGameConditions();	 // Проверка: выигрыш или проигрыш
	void checkLoseCondition();	 // Условие проигрыша
	void checkWinCondition();	 // Условие победы

	// === Проверка коллизий ===
	void checkCollisions();
	void checkBrickCollisions();

	// === Экран победы/поражения ===
	void showWinScreen();	   // Показать экран победы
	void handleScreenInput();  // Обработка ввода на экране победы
	void showLoseScreen();	   // Показать экран поражения
	// void handleLoseScreenInput();  // Обработка ввода на экране поражения
	void resetGame();  // Сбросить игру в начальное состояние

	// === Система сохранения/загрузки ===
	void saveGame();			   // Сохранить текущее состояние игры
	void loadGame();			   // Загрузить состояние игры  
	bool hasSavedGame() const;     // Проверить наличие сохранения
	void createSaveData(GameSaveData& data); // Создать данные для сохранения
	void applySaveData(const GameSaveData& saveData); // Применить загруженные данные



	// === Ресурсы и отображение ===
	static TextureManager textureManager;  // Менеджер текстур
	ScoreSystem scoreSystem_;			   // Система подсчёта очков
	sf::Text scoreText_;				   // Текст для отображения текущих очков
	sf::Text highscoreText_;			   // Текст для отображения рекорда
	sf::Font font_;						   // Используемый шрифт
	sf::Text winText_;					   // Текст победы
	sf::Text loseText_;					   // Текст поражения
	sf::Sprite background_;				   // Задний фон
	SaveSystem saveSystem_;                // Система сохранений

	// === Игровые объекты ===
	std::unique_ptr<sf::RenderWindow> window_;	  // Основное окно SFML
	std::unique_ptr<Platform> platform_;		  // Платформа игрока
	std::unique_ptr<Ball> ball_;				  // Игровой мяч
	std::vector<std::unique_ptr<Brick>> blocks_;  // Кирпичи (старое имя, не используется?)
	std::vector<Bonus> bonuses_;				  // Активные бонусы на сцене
	std::unique_ptr<MenuState> menuState_;	      // Экран меню
	std::map<BonusType, float> bonusTimeOffsets_; // Смещение времени для восстановленных бонусов


	// === Меню ===
	void initMenu();						      // Инициализация меню
	void startGame();						      // Новая игра
	void exitGame();							  // Выход
	void continueGame();						  // Продолжить игру

	// === Состояния игры ===
	StateScreen stateScreen;  // Состояние экрана

	// === Параметры физики ===
	float currentBallSpeedMultiplier_;			  // Текущий множитель скорости мяча
	float ballSpeedChangeTimer_;				  // Таймер для изменения скорости мяча
	const float ballSpeedChangeInterval_ = 1.0f;  // Интервал между изменениями скорости
	const float minBallSpeedMultiplier_ = 1.0f;	  // Минимальная скорость мяча
	const float maxBallSpeedMultiplier_ = 1.5f;	  // Максимальная скорость мяча

												  // Test Fireball mechanic
	// sf::Clock bonusClockTimer_;
	// BonusType currentBonusActivity = BonusType::None;
	std::map<BonusType, sf::Clock> activeBonuses_;
};