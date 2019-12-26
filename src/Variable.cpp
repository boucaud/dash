#include "Variable.h"

#include <iostream>
#include <sstream>
Variable::Variable(const std::vector<std::string>& values)
{
    if (values.empty())
    {
        return;
    }

    this->set(values);
}

Variable::Variable(const std::string& value)
{
    if (value.empty())
    {
        this->values.clear();
    }
    else
    {
        this->values[0] = value;
    }
}

std::string Variable::getValue(unsigned int index) const
{
    if (this->values.empty() || this->values.count(index) == 0)
    {
        return std::string();
    }
    return this->values.at(index);
}

unsigned int Variable::getCount() const { return this->values.size(); }

void Variable::set(const std::string& value, unsigned int index)
{
    if (value.empty())
    {
        this->values.erase(index);
    }
    else
    {
        this->values[index] = value;
    }
}

void Variable::set(const std::vector<std::string>& vals)
{
    if (vals.empty())
    {
        this->clear();
    }
    else
    {
        for (unsigned int i = 0; i < vals.size(); ++i)
        {
            this->values[i] = vals[i];
        }
    }
}

void Variable::clear() { this->values.clear(); }
