#include "Environment.h"

bool Environment::has(const std::string& name) const
{
    return this->globalVariables.count(name) > 0 ||
           this->localVariables.count(name) > 0;
}

void Environment::set(
    const std::string& name, const Variable& variable, bool isGlobal)
{
    if (name.empty() || variable.getCount() == 0)
    {
        return;
    }

    Environment::VariableMapType& variableMap =
        isGlobal ? this->globalVariables : this->localVariables;
    variableMap[name] = variable;
}

Variable& Environment::get(const std::string& name)
{
    if ((this->localVariables.count(name) == 0 &&
            this->globalVariables.count(name) == 0))
    {
        this->localVariables[name] = Variable();
        return this->localVariables[name];
    }
    if (this->localVariables.count(name))
    {
        return this->localVariables[name];
    }
    return this->globalVariables[name];
}
