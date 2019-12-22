#include "echo.h"
#include "../Builtin.h"

#include <iostream>

namespace Builtins
{
int echo(ParserState& state, BuiltinStreams& streams, int argc, char** argv)
{
    std::cout << "echoing stuff" << std::endl;
    return EXIT_SUCCESS;
}
}