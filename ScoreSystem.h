#pragma once
#include <vector>
#include <functional>
#include <unordered_map>


class ScoreSystem {
public:
    enum class BrickType { Normal, Strong, Glass };

    void addObserver(std::function<void(int)> observer);
    void addScore(BrickType type);
    int getCurrentScore() const;
    void saveToHighscores();
    void readToHighscrores();
    const std::vector<int>& getHighscores() const;

private:
    std::vector<std::function<void(int)>> observers_;
    std::unordered_map<BrickType, int> scoreValues_ = {
        {BrickType::Normal, 10},
        {BrickType::Strong, 30},
        {BrickType::Glass, 5}
    };
    int currentScore_ = 0;
    std::vector<int> highscores_;

    void notifyObservers();
};