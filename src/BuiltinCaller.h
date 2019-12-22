#ifndef BUILTIN_CALLER_H
#define BUILTIN_CALLER_H

#include <unordered_map>
#include <string>
#include <functional>

#include "Builtin.h"

class BuiltinCaller{
    public:
    static void RegisterBuiltin(const std::string& name, BuiltinType builtin);
    static void CallBuiltin(const std::string& name);

    private:
    using BuiltinMapType = std::unordered_map<std::string, BuiltinType>;
    static BuiltinMapType Builtins;
};

#endif


