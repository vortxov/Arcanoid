#include "Menu.h"

Menu::Menu(float width, float height) : selectedItemIndex_(0) {
    if (!font_.loadFromFile("arial.ttf")) {
        // Обработка ошибки загрузки шрифта
    }

    std::string items[] = { "Start Game", "Exit" };
    for (size_t i = 0; i < 2; ++i) {
        sf::Text text(items[i], font_, 50);
        text.setPosition(width / 2 - text.getGlobalBounds().width / 2,
            height / 2 + i * 80);
        menuItems_.push_back(text);
    }

    menuItems_[0].setFillColor(sf::Color::Red);
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems_) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex_ > 0) {
        menuItems_[selectedItemIndex_].setFillColor(sf::Color::White);
        selectedItemIndex_--;
        menuItems_[selectedItemIndex_].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex_ + 1 < menuItems_.size()) {
        menuItems_[selectedItemIndex_].setFillColor(sf::Color::White);
        selectedItemIndex_++;
        menuItems_[selectedItemIndex_].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedItem() const {
    return selectedItemIndex_;
}