#include "set.h"
#include "../Builtin.h"

#include <algorithm>
#include <iostream>

namespace Builtins
{
int set(ParserState& state,
    BuiltinStreams& streams,
    const std::vector<std::string>& argv)
{
    if (argv.size() < 3)
    {
        streams.err << "Usage: set <name> <value>" << std::endl;
    }
    std::string name = argv[1];
    state.getEnvironment().get(name).append(
        std::vector<std::string>(argv.begin() + 2, argv.end()));
    return EXIT_SUCCESS;
}
}  // namespace Builtins
