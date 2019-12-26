#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "BuiltinCaller.h"
#include "builtins/set.h"
#include "builtins/echo.h"

#define ERROR_MACRO(message) std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << " " << message << std::endl; std::exit(EXIT_FAILURE);

// TODO: move ofc
ParserState state;

void initialize()
{
    // TODO: move
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

std::string::const_iterator getNextQuote(const std::string::const_iterator& begin, const std::string::const_iterator& end) {
    auto quote = *begin;
    std::string::const_iterator it = begin + 1;
    while(it != end) {
        if(*it == '\\') {
            ++it;
        } else if(*it == quote) {
            return it;
        }
        ++it;
    }
    return end;
}

bool isAlphaNumeric(char c) {
    return c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

std::string::const_iterator getNextToken(const std::string& line, const std::string::const_iterator &begin)
{
    bool isEscaping = false;
    bool isInBrackets = false;
    int numberOfParens = 0;

    std::string::const_iterator it = begin;
    while(it != line.end()) {
        char c = *it;
        if(isEscaping) {
            isEscaping = false;
        } else if (isAlphaNumeric(c)) {
            // shortcut if alphanumeric
        }
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
            auto quoteEnd = getNextQuote(it, line.end());
            if(quoteEnd == line.end()) {
                ERROR_MACRO("Quotes are not balanced");
            }
            it = quoteEnd;
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

std::string::const_iterator getNextWord(const std::string::const_iterator& begin, const std::string::const_iterator& end) {
    std::string::const_iterator it = begin + 1;
    while(it != end) {
        if(!isAlphaNumeric(*it)) {
            break;
        }
        ++it;
    }
    return it;
}

std::string expandToken(const std::string& token, bool supportQuotes = true)
{
    auto it = token.begin();
    auto end = token.end();

    std::string result;
    result.reserve(token.size());

    while(it != end)
    {
        switch(*it)
        {
            case '$':{
                auto endNameIt = getNextWord(it, end);
                if(it + 1 == endNameIt) {
                    ERROR_MACRO("Expected variable name after '$'");
                }
                result.append(state.getEnvironment().get(std::string(it+1, endNameIt)).getValue());
                it = endNameIt - 1;
            }
            break;
            case '\'':
            if(supportQuotes) {
                auto quoteEnd = getNextQuote(it, end);
                result.append(it + 1, quoteEnd);
                it = quoteEnd;
            } else {
                result.push_back(*it);
            }
            break;
            case '"': {
                auto quoteEnd = getNextQuote(it, end);
                std::string quotedString = expandToken(std::string(it+1, quoteEnd), false);
                result.append(quotedString);
                it = quoteEnd;
            }
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

    if(tokens.empty()) {
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