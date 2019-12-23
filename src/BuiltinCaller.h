#ifndef BUILTIN_CALLER_H
#define BUILTIN_CALLER_H

#include <unordered_map>

#include "Builtin.h"

class BuiltinCaller{
    public:
    static bool HasBuiltin(const std::string& name);
    static void RegisterBuiltin(const std::string& name, BuiltinFunctionType* builtin);
    static void CallBuiltin(const std::string& name, ParserState& state, const std::vector<std::string>& argv);

    private:
    using BuiltinMapType = std::unordered_map<std::string, BuiltinFunctionType*>;
    static BuiltinMapType Builtins;
};

#endif


