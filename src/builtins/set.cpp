#include "set.h"
#include "../Builtin.h"

#include <iostream>

namespace Builtins
{
int set(ParserState& state, BuiltinStreams& streams, int argc, char** argv)
{
    std::cout << "Setting var" << std::endl;
}
}