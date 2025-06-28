#include "ScoreSystem.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void ScoreSystem::addObserver(std::function<void(int)> observer)
{
	observers_.push_back(observer);
}

void ScoreSystem::addScore(BrickType type)
{
	currentScore_ += scoreValues_[type];
	notifyObservers();
}

int ScoreSystem::getCurrentScore() const
{
	return currentScore_;
}

void ScoreSystem::saveToHighscores()
{
	highscores_.push_back(currentScore_);
	std::sort(highscores_.rbegin(), highscores_.rend());
	if (highscores_.size() > 5)
		highscores_.resize(5);

	// Сохранение в файл
	std::ofstream file("highscores.txt");  // TODO: убрать 5 одинаковых сохранений
	for (int score : highscores_)
	{
		file << score << "\n";
	}
	currentScore_ = 0;
}

void ScoreSystem::readToHighscrores()
{
	std::ifstream file("highscores.txt");

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{										   // Читаем файл построчно
			std::stringstream ss(line);			   // Создаем строковый поток из строки
			int score;
			if (ss >> score)
			{									   // Пытаемся извлечь число из строки
				if (score != 0)
				{
					highscores_.push_back(score);  // Добавляем число в вектор
				}
			}
			else
			{
				// Обработка ошибки: строка не является числом
				std::cerr << "Ошибка: Некорректная строка в файле: " << line << std::endl;
			}
		}
		file.close();  // Закрываем файл
	}
	else
	{
		// Обработка ошибки: не удалось открыть файл
		std::cerr << "Ошибка: Не удалось открыть файл: " << "highscores.txt" << std::endl;
	}
}

const std::vector<int>& ScoreSystem::getHighscores() const
{
	return highscores_;
}

void ScoreSystem::notifyObservers()
{
	for (auto& observer : observers_)
	{
		observer(currentScore_);
	}
}