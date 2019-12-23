#ifndef BUILTIN_H
#define BUILTIN_H


#include <functional>
#include <sstream>

#include "ParserState.h"

struct BuiltinStreams{
    // TODO: first 2 as const?
    std::stringstream in;
    std::stringstream err;
    std::stringstream out;
};

using BuiltinFunctionType = int(ParserState& state, BuiltinStreams& streams, int argc, char** argv);
using BuiltinType = std::function<BuiltinFunctionType>;

#endif