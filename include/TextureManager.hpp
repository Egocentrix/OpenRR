#pragma once

#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    void registerTexture(const std::string &key, const std::string &filename);
    std::shared_ptr<sf::Texture> getTexture(const std::string &key);

private:
    std::unordered_map<std::string, std::string> filenames;
    std::unordered_map<std::string, std::weak_ptr<sf::Texture>> textures;
};
