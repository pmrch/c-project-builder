#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "config.h"
#include "flags.h"
#include "utils.h"
#include "path.h"
#include "log.h"

Strictness validate_strictness(const char* level_str) {
    char *end;

    errno = 0;
    long level = strtol(level_str, &end, 10);
    int is_integer = (errno != ERANGE && *end == '\0');

    if (is_integer) {
        if (level == 3) { return Strict; }
        else if (level == 2) { return Moderate; }
        else if (level == 1) { return Lint; }
        else if (level == 0) { return Lazy; }
    } 
    
    LOG_WARN("Invalid strictness level '%s' was set, defaulting to moderate", level_str);
    return Moderate;
}

const char* delegate_strictness_flags(const Strictness level) {
    if (level == Strict) { return STRICT_FLAGS; }
    if (level == Moderate) { return MODERATE_FLAGS; }
    if (level == Lint) { return LINT_FLAGS; }
    
    return " ";
}

const char* join_cflags(const CompilerOptions *opts) {
    char cflags[PATH_MAX] = { 0 };

    if (opts->compiler_set) {
        
    }
}