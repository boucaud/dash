#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "BuiltinCaller.h"
#include "builtins/set.h"
#include "builtins/echo.h"

#define ERROR_MACRO(message) std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << " " << message << std::endl; std::exit(EXIT_FAILURE);
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

bool isSeparator(char c) {
    switch(c) {
        case '\0':
        case ' ':
        case '\n':
        case '|':
        case ';':
        case '\t':
        case '\r':
        case '<':
        case '>':
        case '&':
            return true;
        default:
        return false;
    }
}

std::string::const_iterator getNextToken(const std::string& line, const std::string::const_iterator &begin)
{
    bool isEscaping = false;
    bool isInBrackets = false;
    int numberOfParens = 0;
    // TODO: support {}???

    std::string::const_iterator it = begin;
    while(it != line.end()) {
        char c = *it;
        if(isEscaping) {
            isEscaping = false;
        }
        // TODO: shortcut if alphanumeric
        else if(c == '\\') {
            isEscaping = true;
        } else if(c == '(') {
            numberOfParens++;
        } else if(c == ')') {
            if(numberOfParens == 0) {
                ERROR_MACRO("Unmatched ')'\n");
            }
            numberOfParens --;
        } else if(c == '['){
            if(it != begin) {
                isInBrackets = true;
            }
        } else if(c == ']') {
            if(isInBrackets && numberOfParens == 0) {
                isInBrackets = false;
            }
        }
        else if(c == '\'' || c == '"') {
            //TODO: jump to matching
            while(++it != line.end()) {
                if(*it == '\\') {
                    ++it;
                } else if(*it == c) {
                    break;
                }
            }
            if(it == line.end()) {
                ERROR_MACRO("\\ at end of line");
            }
        } else if(isSeparator(c) && !isInBrackets && !isEscaping && numberOfParens == 0) {
            break;
        }
        ++it;
    }

    if(numberOfParens > 0) {
        ERROR_MACRO("Mismatched parenthesis");
    }
    if(isInBrackets) {
        ERROR_MACRO("Mismatched brackets");
    }

    return it;
}

// TODO: tokens can have separators
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
    std::vector<std::string> tokens;
    std::string::const_iterator it = line.begin();
    while(it != line.end())
    {
        auto nextIt = getNextToken(line, it);
        std::string token(it, nextIt);

        if(!token.empty())
        {
            std::string expanded = expandToken(token);
            if(!expanded.empty())
            {
                tokens.push_back(expanded);
            }
        }
        if(nextIt == line.end()) {
            break;
        }
        it = nextIt + 1;
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