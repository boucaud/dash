#include "echo.h"
#include "../Builtin.h"

#include <iostream>

namespace Builtins
{
int echo(ParserState& state,
    BuiltinStreams& streams,
    const std::vector<std::string>& argv)
{
    auto end = argv.end();
    for (auto it = argv.begin() + 1; it != end; ++it)
    {
        streams.out << *it;
        if (it + 1 != end)
        {
            streams.out << " ";
        }
    }
    streams.out << std::endl;
    return EXIT_SUCCESS;
}
}  // namespace Builtins
