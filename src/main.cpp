#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "BuiltinCaller.h"
#include "builtins/echo.h"
#include "builtins/set.h"

#define ERROR_MACRO(message)                                                \
    std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << " " << message \
              << std::endl;                                                 \
    std::exit(EXIT_FAILURE);

// TODO: move ofc
ParserState state;

void initialize()
{
    // TODO: move
    BuiltinCaller::RegisterBuiltin("set", Builtins::set);
    BuiltinCaller::RegisterBuiltin("echo", Builtins::echo);
}

void prompt() { std::cout << "$ "; }

bool isSeparator(char c)
{
    switch (c)
    {
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

std::string::const_iterator getNextQuote(
    const std::string::const_iterator& begin,
    const std::string::const_iterator& end)
{
    auto quote = *begin;
    std::string::const_iterator it = begin + 1;
    while (it != end)
    {
        if (*it == '\\')
        {
            ++it;
        }
        else if (*it == quote)
        {
            return it;
        }
        ++it;
    }
    return end;
}

bool isAlphaNumeric(char c)
{
    return c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

std::string::const_iterator getNextToken(
    const std::string& line, const std::string::const_iterator& begin)
{
    bool isEscaping = false;
    bool isInBrackets = false;
    int numberOfParens = 0;

    std::string::const_iterator it = begin;
    while (it != line.end())
    {
        char c = *it;
        if (isEscaping)
        {
            isEscaping = false;
        }
        else if (isAlphaNumeric(c))
        {
            // shortcut if alphanumeric
        }
        else if (c == '\\')
        {
            isEscaping = true;
        }
        else if (c == '(')
        {
            numberOfParens++;
        }
        else if (c == ')')
        {
            if (numberOfParens == 0)
            {
                ERROR_MACRO("Unmatched ')'\n");
            }
            numberOfParens--;
        }
        else if (c == '[')
        {
            if (it != begin)
            {
                isInBrackets = true;
            }
        }
        else if (c == ']')
        {
            if (isInBrackets && numberOfParens == 0)
            {
                isInBrackets = false;
            }
        }
        else if (c == '\'' || c == '"')
        {
            auto quoteEnd = getNextQuote(it, line.end());
            if (quoteEnd == line.end())
            {
                ERROR_MACRO("Quotes are not balanced");
            }
            it = quoteEnd;
        }
        else if (isSeparator(c) && !isInBrackets && !isEscaping &&
                 numberOfParens == 0)
        {
            break;
        }
        ++it;
    }

    if (numberOfParens > 0)
    {
        ERROR_MACRO("Mismatched parenthesis");
    }
    if (isInBrackets)
    {
        ERROR_MACRO("Mismatched brackets");
    }

    return it;
}

std::string::const_iterator getNextWord(
    const std::string::const_iterator& begin,
    const std::string::const_iterator& end)
{
    std::string::const_iterator it = begin + 1;
    while (it != end)
    {
        if (!isAlphaNumeric(*it))
        {
            break;
        }
        ++it;
    }
    return it;
}

std::string::const_iterator getNextSymbol(
    const std::string::const_iterator& begin,
    const std::string::const_iterator& end,
    char symbol)
{
    std::string::const_iterator it = begin + 1;
    while (it != end)
    {
        if (*it == '\\')
        {
            ++it;
            if (it == end)
            {
                ERROR_MACRO(std::string("Missing ") + symbol);
            }
        }
        else if (*it == symbol)
        {
            return it;
        }
        ++it;
    }
    ERROR_MACRO(std::string("Missing ") + symbol);
}

std::string expandToken(const std::string& token, bool supportQuotes = true)
{
    auto it = token.begin();
    auto end = token.end();

    std::string result;
    result.reserve(token.size());

    while (it != end)
    {
        switch (*it)
        {
            case '$':
            {
                int index = 0;
                auto endNameIt = getNextWord(it, end);
                if (it + 1 == endNameIt)
                {
                    ERROR_MACRO("Expected variable name after '$'");
                }
                std::string varName(it + 1, endNameIt);
                if (*endNameIt == '[')
                {
                    auto closingBracket = getNextSymbol(endNameIt, end, ']');
                    std::string bracketContents =
                        expandToken(std::string(endNameIt + 1, closingBracket));
                    try
                    {
                        index = std::stoi(bracketContents);
                    }
                    catch (const std::exception& e)
                    {
                        ERROR_MACRO("Invalid index value");
                    }
                    it = closingBracket;
                }
                else
                {
                    it = endNameIt - 1;
                }
                result.append(
                    state.getEnvironment().get(varName).getValue(index));
            }
            break;
            case '\'':
                if (supportQuotes)
                {
                    auto quoteEnd = getNextQuote(it, end);
                    result.append(it + 1, quoteEnd);
                    it = quoteEnd;
                }
                else
                {
                    result.push_back(*it);
                }
                break;
            case '"':
            {
                auto quoteEnd = getNextQuote(it, end);
                std::string quotedString =
                    expandToken(std::string(it + 1, quoteEnd), false);
                result.append(quotedString);
                it = quoteEnd;
            }
            break;
            case '\\':
                if (it + 1 != end)
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
std::vector<std::string> parseLine(const std::string& line)
{
    std::vector<std::string> tokens;
    if (line.empty())
    {
        return tokens;
    }
    std::string::const_iterator it = line.begin();
    std::string::const_iterator previousIt = it;
    while (it != line.end())
    {
        auto nextIt = getNextToken(line, it);
        // TODO: get separator type from this string.
        std::string separator(previousIt, it);
        std::string token(it, nextIt);
        if (!token.empty())
        {
            std::string expanded = expandToken(token);
            if (!expanded.empty())
            {
                tokens.push_back(expanded);
            }
        }
        if (nextIt == line.end())
        {
            break;
        }
        previousIt = nextIt;
        it = nextIt + 1;
    }

    return tokens;
}

void mainLoop()
{
    std::string line;
    while (!std::cin.eof())
    {
        prompt();
        std::getline(std::cin, line);
        auto tokens = parseLine(line);

        const std::string command = tokens[0];
        if (BuiltinCaller::HasBuiltin(command))
        {
            BuiltinCaller::CallBuiltin(command, state, tokens);
        }
    }
}

void shutDown() {}

int main(int argv, char** argc)
{
    initialize();

    mainLoop();

    shutDown();

    return EXIT_SUCCESS;
}
