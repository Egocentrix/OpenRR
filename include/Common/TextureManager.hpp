#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "ResourceManager.hpp"

class TextureManager : public ResourceManager<sf::Texture>
{
public:
    void registerResource(const std::string &key, const std::string &filename) override;
    std::shared_ptr<sf::Texture> getResource(const std::string &key) override;

private:
    std::unordered_map<std::string, std::string> filenames;
    std::unordered_map<std::string, std::weak_ptr<sf::Texture>> textures;
};
