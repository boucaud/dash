#ifndef ECHO_H
#define ECHO_H

#include "../Builtin.h"
namespace Builtins
{
int echo(ParserState& state, BuiltinStreams& streams, int argc, char** argv);
}

#endif