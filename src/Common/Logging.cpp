#include "Logging.hpp"

#include <iostream>

void Logger::Log(const std::string &message)
{
    std::cout << message << std::endl;
}

void Logger::Log(const std::string &source, const std::string &message)
{
    auto combinedmessage = "[" + source + "] \t" + message; 
    Log(combinedmessage);
}
