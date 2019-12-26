#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>

class Variable
{
   public:
    Variable() = default;
    Variable(const std::vector<std::string>& values);
    Variable(const std::string& value);

    std::string getValue(unsigned int index = 0) const;
    unsigned int getCount() const;

    void append(const std::string& value);
    void append(const std::vector<std::string>& values);

    void prepend(const std::string& value);
    void prepend(const std::vector<std::string>& values);

    std::string toString() const;

   private:
    std::vector<std::string> values;
};

#endif
