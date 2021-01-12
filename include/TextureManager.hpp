#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    void loadTexture(const std::string &key, const std::string &filename);
    sf::Texture &getRef(const std::string &key);

private:
    std::map<std::string, sf::Texture> textures{};
};
