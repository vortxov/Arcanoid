#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window, sf::Font& font)
    : window_(window), font_(font), selectedIndex_(0), isActive_(false)
{
    // Настройка заголовка
    titleText_.setFont(font_);
    titleText_.setCharacterSize(48);
    titleText_.setFillColor(sf::Color::White);
    titleText_.setString("ARKANOID");
    
    sf::FloatRect bounds = titleText_.getLocalBounds();
    titleText_.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    titleText_.setPosition(window_.getSize().x / 2.f, 150.f);
}

void MenuState::handleInput(sf::Event& event)
{
    if (!isActive_ || menuItems_.empty()) return;
    
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
            selectedIndex_ = (selectedIndex_ - 1 + menuItems_.size()) % menuItems_.size();
            updateSelection();
            break;
            
        case sf::Keyboard::Down:
            selectedIndex_ = (selectedIndex_ + 1) % menuItems_.size();
            updateSelection();
            break;
            
        case sf::Keyboard::Enter:
        case sf::Keyboard::Space:
            executeSelectedAction();
            break;
        }
    }
}

void MenuState::update(float deltaTime)
{
    // Здесь можно добавить анимации для меню
}

void MenuState::render()
{
    if (!isActive_) return;
    
    window_.clear();
    
    // Отрисовка фона
    window_.draw(background_);
    
    // Отрисовка заголовка
    window_.draw(titleText_);
    
    // Отрисовка пунктов меню
    for (const auto& item : menuItems_)
    {
        window_.draw(item.text);
    }
    
    window_.display();
}

void MenuState::addMenuItem(const std::string& text, std::function<void()> action)
{
    MenuItem item;
    item.text.setFont(font_);
    item.text.setCharacterSize(32);
    item.text.setFillColor(sf::Color::White);
    item.text.setString(text);
    item.action = action;
    
    float yPosition = 250.f + menuItems_.size() * 60.f;
    centerMenuItem(item.text, yPosition);
    
    menuItems_.push_back(item);
    
    if (menuItems_.size() == 1)
    {
        updateSelection(); // Выделить первый элемент
    }
}

void MenuState::setBackground(const sf::Texture& texture)
{
    background_.setTexture(texture);
}

void MenuState::updateSelection()
{
    for (size_t i = 0; i < menuItems_.size(); ++i)
    {
        if (i == selectedIndex_)
        {
            menuItems_[i].text.setFillColor(sf::Color::Yellow);
            menuItems_[i].isSelected = true;
        }
        else
        {
            menuItems_[i].text.setFillColor(sf::Color::White);
            menuItems_[i].isSelected = false;
        }
    }
}

void MenuState::executeSelectedAction()
{
    if (selectedIndex_ >= 0 && selectedIndex_ < menuItems_.size())
    {
        if (menuItems_[selectedIndex_].action)
        {
            menuItems_[selectedIndex_].action();
        }
    }
}

void MenuState::centerMenuItem(sf::Text& text, float yPosition)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    text.setPosition(window_.getSize().x / 2.f, yPosition);
}
