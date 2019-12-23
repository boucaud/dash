#include "set.h"
#include "../Builtin.h"

#include <iostream>

namespace Builtins
{
int set(ParserState& state, BuiltinStreams& streams, const std::vector<std::string>& argv)
{
    std::cout << "Setting var" << std::endl;
    return EXIT_SUCCESS;
}
}