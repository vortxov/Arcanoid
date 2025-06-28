#include "SaveSystem.h"
#include <iostream>
#include <filesystem> 


SaveSystem::SaveSystem()
{
	// Для Windows можно создать папку через system call
	#ifdef _WIN32
	system("mkdir saves 2>nul");  // 2>nul подавляет ошибку если папка уже существует
	#else
	system("mkdir -p saves");
	#endif

}

bool SaveSystem::saveGame(const std::string& filename, const GameSaveData& data)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open save file for writing: " << filename << std::endl;
        return false;
    }
    
    try
    {
        // Записываем версию формата
        writeInt(file, SAVE_VERSION);
        
        // Данные мяча
        writeVector2f(file, data.ballPosition);
        writeVector2f(file, data.ballVelocity);
        writeFloat(file, data.ballSpeedMultiplier);
        
        // Данные платформы
        writeVector2f(file, data.platformPosition);
        
        // Счёт
        writeInt(file, data.currentScore);
        
    	writeInt(file, static_cast<int>(data.activeBonusTimers.size()));
    	for (const auto& timerData : data.activeBonusTimers)
    	{
    		writeInt(file, timerData.bonusType);
    		writeFloat(file, timerData.timeElapsed);
    	}

        
        // Количество кирпичей
        writeInt(file, static_cast<int>(data.bricks.size()));
        
        // Данные кирпичей
    	for (const auto& brick : data.bricks)
    	{
    		writeVector2f(file, brick.position);
    		writeInt(file, brick.brickType);
    		writeInt(file, brick.pastBrickType); // Новая строка
    		writeInt(file, brick.hitCount);
    		writeBool(file, brick.isDestroyed);
    		writeInt(file, brick.bonusType);
    	}

        
        // Количество активных бонусов
        writeInt(file, static_cast<int>(data.activeBonuses.size()));
        
        // Данные активных бонусов
        for (const auto& bonus : data.activeBonuses)
        {
            writeVector2f(file, bonus.position);
            writeInt(file, bonus.bonusType);
        }
        
        file.close();
        std::cout << "Game saved successfully to: " << filename << std::endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error saving game: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

bool SaveSystem::loadGame(const std::string& filename, GameSaveData& data)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open save file for reading: " << filename << std::endl;
        return false;
    }
    
    try
    {
        // Проверяем версию формата
        int version = readInt(file);
        if (version != SAVE_VERSION)
        {
            std::cerr << "Incompatible save file version: " << version << std::endl;
            file.close();
            return false;
        }
        
        // Данные мяча
        data.ballPosition = readVector2f(file);
        data.ballVelocity = readVector2f(file);
        data.ballSpeedMultiplier = readFloat(file);
        
        // Данные платформы
        data.platformPosition = readVector2f(file);
        
        // Счёт
        data.currentScore = readInt(file);
        
    	// Активные бонусы с таймерами
    	int bonusTimersCount = readInt(file);
    	data.activeBonusTimers.clear();
    	data.activeBonusTimers.reserve(bonusTimersCount);
        
    	for (int i = 0; i < bonusTimersCount; ++i)
    	{
    		GameSaveData::ActiveBonusTimerData timerData;
    		timerData.bonusType = readInt(file);
    		timerData.timeElapsed = readFloat(file);
    		data.activeBonusTimers.push_back(timerData);
    	}


        
        // Количество кирпичей
        int brickCount = readInt(file);
        data.bricks.clear();
        data.bricks.reserve(brickCount);
        
        // Данные кирпичей
    	for (int i = 0; i < brickCount; ++i)
    	{
    		GameSaveData::BrickData brick;
    		brick.position = readVector2f(file);
    		brick.brickType = readInt(file);
    		brick.pastBrickType = readInt(file); // Новая строка
    		brick.hitCount = readInt(file);
    		brick.isDestroyed = readBool(file);
    		brick.bonusType = readInt(file);
    		data.bricks.push_back(brick);
    	}

        
        // Количество активных бонусов
        int bonusCount = readInt(file);
        data.activeBonuses.clear();
        data.activeBonuses.reserve(bonusCount);
        
        // Данные активных бонусов
        for (int i = 0; i < bonusCount; ++i)
        {
            GameSaveData::ActiveBonusData bonus;
            bonus.position = readVector2f(file);
            bonus.bonusType = readInt(file);
            data.activeBonuses.push_back(bonus);
        }
        
        file.close();
        std::cout << "Game loaded successfully from: " << filename << std::endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading game: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

bool SaveSystem::saveExists(const std::string& filename) const
{
	std::ifstream file(filename);
	return file.good();
}

bool SaveSystem::deleteSave(const std::string& filename)
{
    try
    {
    	return std::remove(filename.c_str()) == 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error deleting save file: " << e.what() << std::endl;
        return false;
    }
}

std::string SaveSystem::getDefaultSaveFilename()
{
    return "saves/game_save.dat";
}

// Методы для записи данных
void SaveSystem::writeBool(std::ofstream& file, bool value)
{
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void SaveSystem::writeInt(std::ofstream& file, int value)
{
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void SaveSystem::writeFloat(std::ofstream& file, float value)
{
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void SaveSystem::writeVector2f(std::ofstream& file, const sf::Vector2f& vec)
{
    writeFloat(file, vec.x);
    writeFloat(file, vec.y);
}

// Методы для чтения данных
bool SaveSystem::readBool(std::ifstream& file)
{
    bool value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

int SaveSystem::readInt(std::ifstream& file)
{
    int value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

float SaveSystem::readFloat(std::ifstream& file)
{
    float value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

sf::Vector2f SaveSystem::readVector2f(std::ifstream& file)
{
    float x = readFloat(file);
    float y = readFloat(file);
    return sf::Vector2f(x, y);
}
