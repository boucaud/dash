#include "BuiltinCaller.h"

BuiltinCaller::BuiltinMapType BuiltinCaller::Builtins;

void BuiltinCaller::RegisterBuiltin(const std::string& name, BuiltinType builtin)
{
    if(name.empty())
    {
        return;
    }
    BuiltinCaller::Builtins[name] = builtin;
}

void BuiltinCaller::CallBuiltin(const std::string& name)
{
    if(name.empty() || BuiltinCaller::Builtins.count(name) == 0)
    {
        return;
    }
    BuiltinType builtin = BuiltinCaller::Builtins[name];

    // TODO: remove
    char toRemove[1][1];
    ParserState p;
    BuiltinStreams b;
    builtin(p, b, 0, nullptr); // TODO: properly call
}

