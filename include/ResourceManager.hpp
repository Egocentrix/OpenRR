#pragma once

#include <memory>

// Interface class for resource managers, e.g. Textures
template <typename T>
class ResourceManager
{
public:
    virtual ~ResourceManager() = default;

    virtual void registerResource(const std::string &key, const std::string &filename) = 0;
    virtual std::shared_ptr<T> getResource(const std::string &key) = 0;
};
