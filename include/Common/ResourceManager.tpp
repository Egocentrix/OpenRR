#include <iostream>

#include "ResourceManager.hpp"

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
    std::cout << "Loading resource from file: " << filename << "\n";
    
    std::shared_ptr<T> resource = loadFromFile(filename);
    
    if (resource != nullptr)
    {
        resources[key] = resource;
    }
    else
    {
        std::cout << "Failed to load file: " << filename << std::endl;
    }
   
    return resource;
}