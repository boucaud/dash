#ifndef PARSER_STATE_H
#define PARSER_STATE_H

#include "Environment.h"

class ParserState{
    public:
    Environment& getEnvironment();
    private:
    Environment env;
};

#endif