#pragma once

// Basic interface for command items
class Command
{
public:
    virtual ~Command() = default;
    virtual std::string describe() const = 0;
    virtual void execute() const = 0;
};