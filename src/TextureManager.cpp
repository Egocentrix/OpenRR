#include "TextureManager.hpp"

void TextureManager::loadTexture(const std::string &key, const std::string &filename)
{
    sf::Texture tex;
    tex.loadFromFile(filename);
    textures[key] = tex;
}

sf::Texture &TextureManager::getRef(const std::string &key)
{
    return textures.at(key);
}