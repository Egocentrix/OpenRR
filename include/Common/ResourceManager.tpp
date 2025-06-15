#include <filesystem>

#include "ResourceManager.hpp"

template <typename T>
void ResourceManager<T>::registerResource(const std::string &key, const std::string &filename)
{
    if (!std::filesystem::exists(filename))
    {
        throw std::runtime_error("Resource not found: " + filename);
    }

    filenames[key] = filename;
}

template <typename T>
std::shared_ptr<T> ResourceManager<T>::getResource(const std::string &key)
{
    // Texture exist and is still valid
    if (resources.count(key) != 0)
    {
        if (!resources.at(key).expired())
        {
            return resources.at(key).lock();
        }
    }

    // Otherwise, load from disk
    auto filename = filenames.at(key);
    logger_.Log(LogLevel::Info, "Loading resource with id '" + key + "' from file: " + filename);

    std::shared_ptr<T> resource = loadFromFile(filename);

    if (resource != nullptr)
    {
        resources[key] = resource;
    }
    else
    {
        logger_.Log(LogLevel::Error, "Failed to load file: " + filename);
    }

    return resource;
}