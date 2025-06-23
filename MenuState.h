#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

enum class StateScreen;

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
	void render();
    
	void addMenuItem(const std::string& text, std::function<void()> action);
	void setBackground(const sf::Texture& texture);
    
	StateScreen GetActive() const { return isActive_; }
	void setActive(StateScreen active) { isActive_ = active; }

private:
	sf::RenderWindow& window_;
	sf::Font& font_;
	std::vector<MenuItem> menuItems_;
	int selectedIndex_;
	StateScreen isActive_;
    
	sf::Sprite background_;
	sf::Text titleText_;
    
	void updateSelection();
	void executeSelectedAction();
	void centerMenuItem(sf::Text& text, float yPosition);

};
