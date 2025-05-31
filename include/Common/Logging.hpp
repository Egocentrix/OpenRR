#pragma once

#include <string>

enum class LogLevel
{
    Info,
    Error
};

class Logger
{
public:
    static void Log(const std::string& message);
    static void Log(const std::string& source, const std::string& message);
    static void Log(LogLevel level, const std::string& source, const std::string& message);

private:
    /* data */
};

