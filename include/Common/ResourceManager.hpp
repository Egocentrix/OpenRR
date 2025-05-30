#pragma once

#include <memory>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>

// Generic class for resource managers, e.g. Textures
template <typename T>
class ResourceManager
{
public:
    virtual ~ResourceManager() = default;

    void registerResource(const std::string &key, const std::string &filename);
    std::shared_ptr<T> getResource(const std::string &key);

private:
    std::unordered_map<std::string, std::string> filenames;
    std::unordered_map<std::string, std::weak_ptr<T>> resources;

    // This function needs to be implemented for each class specialization
    static std::shared_ptr<T> loadFromFile(const std::string &filename);
};

// loadFromFile specializations here
template<>
inline std::shared_ptr<sf::Texture> ResourceManager<sf::Texture>::loadFromFile(const std::string &filename)
{
    auto tex = std::make_unique<sf::Texture>();
    if (tex->loadFromFile(filename))
    {
        std::shared_ptr<sf::Texture> shared(tex.release());
        return shared;
    }
    return nullptr;
}

#include "ResourceManager.tpp"