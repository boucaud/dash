#ifndef BUILTIN_H
#define BUILTIN_H

#include <sstream>
#include <vector>
#include <string>

#include "ParserState.h"

struct BuiltinStreams{
    // TODO: first 2 as const?
    std::stringstream in;
    std::stringstream err;
    std::stringstream out;
};

using BuiltinFunctionType = int(ParserState& state, BuiltinStreams& streams, const std::vector<std::string>& argv);

#endif