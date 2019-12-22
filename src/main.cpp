#include <iostream>
#include <string>

#include "BuiltinCaller.h"
#include "builtins/set.h"
#include "builtins/echo.h"

void initialize()
{
    BuiltinCaller::RegisterBuiltin("set", Builtins::set);
    BuiltinCaller::RegisterBuiltin("echo", Builtins::echo);
}

void prompt()
{
    std::cout << "$ ";
}

void parseLine(const std::string& line)
{
    if(line.empty())
    {
        return;
    }
    if(line.find("echo") != std::string::npos)
    {
        BuiltinCaller::CallBuiltin("echo");
    }
    if(line.find("set") != std::string::npos)
    {
        BuiltinCaller::CallBuiltin("set");
    }
}

void mainLoop()
{
    std::string line;
    while(!std::cin.eof())
    {
        prompt();
        std::getline(std::cin, line);
        parseLine(line);
    }
}

void shutDown()
{
}

int main(int argv, char **argc)
{
    initialize();

    mainLoop();

    shutDown();

    return EXIT_SUCCESS;
}