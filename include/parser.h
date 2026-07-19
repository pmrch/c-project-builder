#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#include "utils.h"

typedef struct {
    const char *lang;
    const char *config;
    const char *compiler;
    u8      strictness;
    bool    lang_set;
    bool    config_set;
    bool    compiler_set;
    bool    strictness_set;
    bool    mimalloc_requested;
} CompilerOptions;

CompilerOptions* parse_compiler_flags(const int argc, const char **argv);

#endif