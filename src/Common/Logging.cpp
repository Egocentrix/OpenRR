#include "Logging.hpp"

#include <iostream>

Logger::Logger(const std::string &name)
: name_{name}
{
}

Logger Logger::create(const std::string &name)
{
    return Logger(name);
}

void Logger::Log(const std::string &message)
{
    Log(LogLevel::Info, message);
}

void Logger::Log(LogLevel level, const std::string &message)
{
    auto sourcePrefix = "[ " + name_ + " ] ";
    switch (level)
    {
    case LogLevel::Info:
        std::cout << sourcePrefix << message << std::endl;
        break;

    case LogLevel::Error:
        std::cerr << sourcePrefix << "ERROR " << message << std::endl;
        break;
    default:
        break;
    }
}
