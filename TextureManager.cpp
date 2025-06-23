#include "TextureManager.h"

void TextureManager::load(const std::string& name, const std::string& path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		throw std::runtime_error("Failed to load texture: " + path);
	}
	textures_[name] = texture;
}

sf::Texture& TextureManager::get(const std::string& name)
{
	auto it = textures_.find(name);
	if (it == textures_.end())
	{
		throw std::runtime_error("Texture not found: " + name);
	}
	return it->second;
}