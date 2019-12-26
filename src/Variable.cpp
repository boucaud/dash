#include "Variable.h"

#include <sstream>

Variable::Variable(const std::vector<std::string>& values)
{
    if (values.empty())
    {
        return;
    }

    this->values.reserve(values.size());
    // Copy one-by-one, to check for empty strings
    for (auto value : values)
    {
        if (!value.empty())
        {
            this->values.push_back(value);
        }
    }
    this->values.shrink_to_fit();
}

Variable::Variable(const std::string& value)
{
    if (value.empty())
    {
        return;
    }
    this->values = std::vector<std::string>(1, value);
}

std::string Variable::getValue(unsigned int index) const
{
    if (this->values.empty() || index >= this->values.size())
    {
        return std::string();
    }
    return this->values[index];
}

unsigned int Variable::getCount() const { return this->values.size(); }

std::string Variable::toString() const
{
    std::stringstream ss;
    bool isFirst = true;
    for (auto value : this->values)
    {
        if (!isFirst)
        {
            ss << " ";
        }
        else
        {
            isFirst = false;
        }
        ss << value;
    }
    return ss.str();
}

void Variable::append(const std::string& value)
{
    if (value.empty())
    {
        return;
    }
    this->values.push_back(value);
}

void Variable::append(const std::vector<std::string>& values)
{
    if (values.empty())
    {
        return;
    }
    // TODO: no check for empty strings
    this->values.reserve(values.size() + this->values.size());
    this->values.insert(this->values.end(), values.begin(), values.end());
}

void Variable::prepend(const std::vector<std::string>& values)
{
    if (values.empty())
    {
        return;
    }
    // TODO: no check for empty strings
    this->values.reserve(values.size() + this->values.size());
    this->values.insert(this->values.begin(), values.begin(), values.end());
}

void Variable::prepend(const std::string& value)
{
    if (value.empty())
    {
        return;
    }
    this->values.insert(this->values.begin(), value);
}
