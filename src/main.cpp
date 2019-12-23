#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "BuiltinCaller.h"
#include "builtins/set.h"
#include "builtins/echo.h"

// TODO: first thing: create class to register all builtins, use it in initialize
// TODO: then -> if not builtin, launch program

// TODO: move ofc
ParserState state;

void initialize()
{
    BuiltinCaller::RegisterBuiltin("set", Builtins::set);
    BuiltinCaller::RegisterBuiltin("echo", Builtins::echo);
}

void prompt()
{
    std::cout << "$ ";
}

std::string expandToken(const std::string& token)
{
    auto it = token.begin();
    auto end = token.end();

    std::string result;
    result.reserve(token.size());

    while(it != end)
    {
        switch(*it)
        {
            case '$':
                result.append(state.getEnvironment().get(std::string(it+1, end)).getValue());
                return result;
            break;
            case '\\':
                if(it + 1 != end)
                {
                    result.push_back(*(++it));
                }
            break;
            default:
                result.push_back(*it);
        }
        ++it;
    }
    return result;
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
            std::string expanded = expandToken(temp);
            if(!expanded.empty())
            {
                tokens.push_back(expanded);
            }
        }
    }

    if(tokens.empty())
    {
        return;
    }

    const std::string command = tokens[0];
    if(BuiltinCaller::HasBuiltin(command))
    {
        BuiltinCaller::CallBuiltin(command, state, tokens);
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