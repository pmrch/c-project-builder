#ifndef PARSER_H
#define PARSER_H

#include "config.h"

char* construct_compiler_flags(const CompilerConfig *cfg, const int argc, const char **argv);

#endif