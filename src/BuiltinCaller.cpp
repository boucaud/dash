#include "BuiltinCaller.h"

#include <iostream>

BuiltinCaller::BuiltinMapType BuiltinCaller::Builtins;

bool BuiltinCaller::HasBuiltin(const std::string& name)
{
    if(name.empty())
    {
        return false;
    }
    return BuiltinCaller::Builtins.count(name) != 0;
}
void BuiltinCaller::RegisterBuiltin(const std::string& name, BuiltinFunctionType* builtin)
{
    if(name.empty())
    {
        return;
    }
    BuiltinCaller::Builtins[name] = builtin;
}

void BuiltinCaller::CallBuiltin(const std::string& name, const std::vector<std::string>& argv)
{
    if(name.empty() || BuiltinCaller::Builtins.count(name) == 0)
    {
        return;
    }
    auto builtin = BuiltinCaller::Builtins[name];

    // TODO: remove
    char toRemove[1][1];
    ParserState p;
    BuiltinStreams b;
    builtin(p, b, argv); // TODO: properly call
    std::cout <<b.out.str();
}
