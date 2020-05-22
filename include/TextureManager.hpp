#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class TextureManager
{
private:
    std::map<std::string, sf::Texture> textures;

public:
    TextureManager(/* args */);
    ~TextureManager();

    void loadTexture(const std::string &key, const std::string &filename);
    sf::Texture &getRef(const std::string &key);
};
