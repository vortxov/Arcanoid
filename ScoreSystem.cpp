#include "ScoreSystem.h"
#include <algorithm>
#include <fstream>

void ScoreSystem::addObserver(std::function<void(int)> observer) {
    observers_.push_back(observer);
}

void ScoreSystem::addScore(BrickType type) {
    currentScore_ += scoreValues_[type];
    notifyObservers();
}

int ScoreSystem::getCurrentScore() const {
    return currentScore_;
}

void ScoreSystem::saveToHighscores() {
    highscores_.push_back(currentScore_);
    std::sort(highscores_.rbegin(), highscores_.rend());
    if (highscores_.size() > 5) highscores_.resize(5);

    // Сохранение в файл
    std::ofstream file("highscores.txt"); //TODO: убрать 5 одинаковых сохранений
    for (int score : highscores_) {
        file << score << "\n";
    }
}

const std::vector<int>& ScoreSystem::getHighscores() const {
    return highscores_;
}

void ScoreSystem::notifyObservers() {
    for (auto& observer : observers_) {
        observer(currentScore_);
    }
}