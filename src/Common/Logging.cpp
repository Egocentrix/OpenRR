#include "Logging.hpp"

#include <iostream>

void Logger::Log(const std::string &message)
{
    Log(LogLevel::Info, "DefaultLogger", message);
}

void Logger::Log(const std::string &source, const std::string &message)
{
    Log(LogLevel::Info, source, message);
}

void Logger::Log(LogLevel level, const std::string &source, const std::string &message)
{
    auto sourcePrefix = "[ " + source + " ] ";
    switch (level)
    {
    case LogLevel::Info:
        std::cout << sourcePrefix << message << std::endl;
        break;
    
    case LogLevel::Error:
        std::cerr << sourcePrefix << "ERROR " << message  << std::endl;
        break;
    default:
        break;
    }
}
