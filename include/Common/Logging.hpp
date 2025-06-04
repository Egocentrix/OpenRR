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
    static Logger create(const std::string& name);

    void Log(const std::string& message);
    void Log(LogLevel level, const std::string& message);

private:
    Logger(const std::string& name);

    std::string name_;
};

