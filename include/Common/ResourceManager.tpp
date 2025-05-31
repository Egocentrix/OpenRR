#include "ResourceManager.hpp"

#include "Logging.hpp"

template <typename T>
void ResourceManager<T>::registerResource(const std::string &key, const std::string &filename)
{
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
    Logger::Log(LogLevel::Info, "ResourceManager", "Loading resource from file: " + filename);

    std::shared_ptr<T> resource = loadFromFile(filename);
    
    if (resource != nullptr)
    {
        resources[key] = resource;
    }
    else
    {
        Logger::Log(LogLevel::Error, "ResourceManager", "Failed to load file: " + filename);
    }
   
    return resource;
}