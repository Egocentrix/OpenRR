#pragma once

#include <string>

class Logger
{
public:
    static void Log(const std::string& message);
    static void Log(const std::string& source, const std::string& message);

private:
    /* data */
};

