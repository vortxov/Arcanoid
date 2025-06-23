#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class MenuState
{
public:
	struct MenuItem
	{
		sf::Text text;
		std::function<void()> action;
		bool isSelected = false;
	};

	MenuState(sf::RenderWindow& window, sf::Font& font);
    
	void handleInput(sf::Event& event);
	void update(float deltaTime);
	void render();
    
	void addMenuItem(const std::string& text, std::function<void()> action);
	void setBackground(const sf::Texture& texture);
    
	bool isActive() const { return isActive_; }
	void setActive(bool active) { isActive_ = active; }

private:
	sf::RenderWindow& window_;
	sf::Font& font_;
	std::vector<MenuItem> menuItems_;
	int selectedIndex_;
	bool isActive_;
    
	sf::Sprite background_;
	sf::Text titleText_;
    
	void updateSelection();
	void executeSelectedAction();
	void centerMenuItem(sf::Text& text, float yPosition);

};
