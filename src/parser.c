#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "parser.h"
#include "config.h"
#include "flags.h"
#include "log.h"

static const char* delegate_strictness_flags(const char* level_str) {
    printf("Delegator got %s\n", level_str);
    if (level_str != NULL && *level_str != '\0') {
        char *end;

        errno = 0;
        long level = strtol(level_str, &end, 10);
        int is_intger = (errno != ERANGE && *end == '\0');
        printf("Level is %zu\n", level);

        if (is_intger) {
            if (level == 3) { return STRICT_FLAGS; }
            else if (level == 2) { return MODERATE_FLAGS; }
            else if (level == 1) { return LINT_FLAGS; }
            else { return ""; }
        }
    }
    
    return "";
}

char* construct_compiler_flags(const CompilerConfig *cfg, const int argc, const char **argv) {
    const char **argv_p = argv;

    char *compiler_flags = malloc(2048);
    if (compiler_flags == NULL) {
        LOG_ERROR("Failed to allocate memory for compiler flags");
        return NULL;
    }

    snprintf(compiler_flags, strlen(cfg->cc) + 1, "%s", cfg->cc);
    while (*++argv_p != NULL) {
        if (strncmp(*argv_p, "--strictness=", 13) == 0) {
            char *level_str = strrchr(*argv_p, '=');
            const char *strictness_flags = delegate_strictness_flags(++level_str);

            if (strictness_flags == NULL) {
                free(level_str);
                return NULL;
            }

            strcat(compiler_flags, " ");
            strcat(compiler_flags, strictness_flags);
        }
    };

    LOG_INFO("We got %d args", argc);
    return compiler_flags;
}