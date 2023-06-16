#include "TextureManager.hpp"

#include <iostream>

void TextureManager::registerResource(const std::string &key, const std::string &filename)
{
    filenames[key] = filename;
}

std::shared_ptr<sf::Texture> TextureManager::getResource(const std::string &key)
{
    // Texture exist and is still valid
    if (textures.count(key) != 0)
    {
        if (!textures.at(key).expired())
        {
            return textures.at(key).lock();
        }
    }

    // Otherwise, load from disk
    std::cout << "loading from file: " << filenames.at(key) << "\n";
    auto tex = std::make_unique<sf::Texture>();
    if (tex->loadFromFile(filenames.at(key)))
    {
        std::shared_ptr<sf::Texture> shared(tex.release());
        textures[key] = shared;
        return shared;
    }

    return nullptr;
}