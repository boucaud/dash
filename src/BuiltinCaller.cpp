#include "BuiltinCaller.h"

#include <iostream>

BuiltinCaller::BuiltinMapType BuiltinCaller::Builtins;

bool BuiltinCaller::HasBuiltin(const std::string& name)
{
    if (name.empty())
    {
        return false;
    }
    return BuiltinCaller::Builtins.count(name) != 0;
}
void BuiltinCaller::RegisterBuiltin(
    const std::string& name, BuiltinFunctionType* builtin)
{
    if (name.empty())
    {
        return;
    }
    BuiltinCaller::Builtins[name] = builtin;
}

void BuiltinCaller::CallBuiltin(const std::string& name,
    ParserState& state,
    const std::vector<std::string>& argv)
{
    if (name.empty() || BuiltinCaller::Builtins.count(name) == 0)
    {
        return;
    }
    auto builtin = BuiltinCaller::Builtins[name];

    BuiltinStreams streams;
    builtin(state, streams, argv);  // TODO: properly call
    std::cout << streams.out.str();
    std::cerr << streams.err.str();
}
