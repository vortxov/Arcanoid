#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

class Block;
class Ball;
class Platform;
class Bonus;
enum class BonusType;

struct GameSaveData
{
    // Данные мяча
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    float ballSpeedMultiplier;
    
    // Данные платформы
    sf::Vector2f platformPosition;
    
    // Счёт
    int currentScore;
    
    // Данные кирпичей (упрощённая структура)
	struct BrickData
	{
		sf::Vector2f position;
		int brickType; // 0-Normal, 1-Strong, 2-Glass
		int pastBrickType; // Предыдущий тип кирпича (для восстановления после бонуса)
		int hitCount; // Для StrongBrick
		bool isDestroyed;
		int bonusType; // Какой бонус содержит
	};

    
    std::vector<BrickData> bricks;

	// Активные бонусы (новая структура для множественных бонусов)
	struct ActiveBonusTimerData
	{
		int bonusType; // Тип бонуса (BonusType -> int)
		float timeElapsed; // Сколько времени уже прошло с активации
	};
	std::vector<ActiveBonusTimerData> activeBonusTimers;

    
    // Активные бонусы на поле
    struct ActiveBonusData
    {
        sf::Vector2f position;
        int bonusType;
    };
    
    std::vector<ActiveBonusData> activeBonuses;
};

class SaveSystem
{
public:
    SaveSystem();
    
    // Сохранение игры
    bool saveGame(const std::string& filename, const GameSaveData& data);
    
    // Загрузка игры
    bool loadGame(const std::string& filename, GameSaveData& data);
    
    // Проверка существования файла сохранения
    bool saveExists(const std::string& filename) const;
    
    // Удаление файла сохранения
    bool deleteSave(const std::string& filename);
    
    // Получить путь к файлу сохранения по умолчанию
    static std::string getDefaultSaveFilename();
    
private:
    static const int SAVE_VERSION = 1; // Версия формата сохранений
    
    // Методы для записи/чтения данных
    void writeBool(std::ofstream& file, bool value);
    void writeInt(std::ofstream& file, int value);
    void writeFloat(std::ofstream& file, float value);
    void writeVector2f(std::ofstream& file, const sf::Vector2f& vec);
    
    bool readBool(std::ifstream& file);
    int readInt(std::ifstream& file);
    float readFloat(std::ifstream& file);
    sf::Vector2f readVector2f(std::ifstream& file);
};

