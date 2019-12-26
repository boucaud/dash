#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>

#include "Variable.h"

class Environment
{
   public:
    Environment() = default;
    bool has(const std::string& name) const;
    void set(const std::string& name,
        const Variable& variable,
        bool isGlobal = false);
    Variable& get(const std::string& name);

   private:
    using VariableMapType = std::unordered_map<std::string, Variable>;
    VariableMapType globalVariables;
    VariableMapType localVariables;
};

#endif
