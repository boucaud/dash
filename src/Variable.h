#ifndef VARIABLE_H
#define VARIABLE_H

#include <map>
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

    void set(const std::string& value, unsigned int index = 0);
    void set(const std::vector<std::string>& values);

    void clear();

   private:
    std::map<unsigned int, std::string> values;
};

#endif
