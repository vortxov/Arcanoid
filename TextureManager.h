#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
public:
    void load(const std::string& name, const std::string& path);
    sf::Texture& get(const std::string& name);

private:
    std::map<std::string, sf::Texture> textures_;
};