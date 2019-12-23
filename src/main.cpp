#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "BuiltinCaller.h"
#include "builtins/set.h"
#include "builtins/echo.h"

// TODO: first thing: create class to register all builtins, use it in initialize
// TODO: then -> tokenize, analyze first word and call builtin (without looking at params)
// TODO: then -> if not builtin, launch program

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
    // TODO: will need to to more if handling quotes
    std::vector<std::string> tokens;
    std::stringstream ss(line);

    std::string temp;
    while(getline(ss, temp, ' '))
    {
        if(!temp.empty())
        {
            tokens.push_back(temp);
        }
    }

    if(tokens.empty())
    {
        return;
    }

    const std::string command = tokens[0];
    if(BuiltinCaller::HasBuiltin(command))
    {
        BuiltinCaller::CallBuiltin(command);
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