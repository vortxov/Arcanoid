#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItem() const;

private:
    int selectedItemIndex_;
    sf::Font font_;
    std::vector<sf::Text> menuItems_;
};