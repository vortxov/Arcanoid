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
	GameState(unsigned int width, unsigned int height);	 // �����������, �������������� ��������� ����
	void run();											 // ������� ������� ����

private:
	// ������������� � ���������
	void initialize();					 // ����� ������������� ����
	void setupWindow();					 // ��������� ����
	void loadResources();				 // �������� ������� � �������
	void initGameObjects();				 // �������� � ���������� ������� ��������
	void setupText();					 // ��������� ������ (����� ������/���������)
	void centerText(sf::Text& text);	 // ������������� ������ �� ������
	void setupScoreDisplay();			 // ���������� ����������� �����
	void updateScoreDisplay(int score);	 // ���������� ������ ����� � ��������

    // Игровая логика
    std::vector<std::unique_ptr<Block>> bricks_;
    void handleEvents();
    void update(float deltaTime);
    void render();
    void handleInput();
    void clampPlatformPosition();
    void updateBall(float deltaTime);
    void updateBallSpeed(float deltaTime);
    void initBricks();
    void pushBonus(Block& brick);
    void updateBonus(float deltaTime);
    void clearBonus();

    // Коллизии
    void checkCollisions();
    void checkWallCollisions();
    void checkPlatformCollision();
    void checkBrickCollisions();
    void handleBrickCollisionResponse(const Block& brick);
    void checkBonusPlatformCollision();

	// �������� ��������
	void checkCollisions();									// �������� ���� ������������
	void checkWallCollisions();								// �������� ������������ ���� �� �������
	void checkPlatformCollision();							// �������� ������������ ���� � ����������
	void checkBrickCollisions();							// �������� ������������ ���� � ���������
	void handleBrickCollisionResponse(const Block& brick);	// ������� �� ������������ � ��������

	// �������� ������� ���������� ����
	void checkGameConditions();	 // �������� ������ ��� ���������
	void checkLoseCondition();	 // �������� ������� ���������
	void checkWinCondition();	 // �������� ������� ������

	// ����� ������/���������
	void showWinScreen();		   // ����������� ������ ������
	void handleWinScreenInput();   // ��������� ����� �� ������ ������
	void showLoseScreen();		   // ����������� ������ ���������
	void handleLoseScreenInput();  // ��������� ����� �� ������ ���������
	void resetGame();			   // ����� ��������� ����

	// ������� � ��������
	static TextureManager textureManager;  // ���������� �������� �������
	ScoreSystem scoreSystem_;			   // ������� �������� �����
	sf::Text scoreText_;				   // ����������� �������� �����
	sf::Text highscoreText_;			   // ����������� ��������
	sf::Font font_;						   // �����
	sf::Text winText_;					   // ����� ������
	sf::Text loseText_;					   // ����� ���������
	sf::Sprite background_;				   // ���

	// ������� �������
	std::unique_ptr<sf::RenderWindow> window_;	  // ���� SFML
	std::unique_ptr<Platform> platform_;		  // ���������
	std::unique_ptr<Ball> ball_;				  // ���
	std::vector<std::unique_ptr<Block>> blocks_;  // ������� (��������, �������� � ��� ���� `bricks_`)
	std::vector<Bonus> bonuses_;				  // �������� ������ �� ����

	// ��������� ����
	bool gameWon_;	 // ���� ������
	bool gameLost_;	 // ���� ���������
	bool onMenu_;	 // ��������� �� ����� � ����

	// ��������� ��������� � ����
	const float platformSpeed_ = 5.0f;			  // �������� ���������
	float currentBallSpeedMultiplier_;			  // ������� ��������� �������� ����
	float ballSpeedChangeTimer_;				  // ������ ��� ��������� ����
	const float ballSpeedChangeInterval_ = 1.0f;  // �������� ���������
	const float minBallSpeedMultiplier_ = 1.0f;	  // ����������� ���������
	const float maxBallSpeedMultiplier_ = 1.5f;	  // ������������ ���������
};