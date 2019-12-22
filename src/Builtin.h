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

using BuiltinType = std::function<int(ParserState& state, BuiltinStreams& streams, int argc, char** argv)>;

#endif