#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "parser.h"
#include "flags.h"
#include "utils.h"
#include "log.h"

#define COMPILER_FLAGS_SIZE 2048

static const char* delegate_strictness_flags(const char* level_str) {
    if (level_str != NULL && *level_str != '\0') {
        char *end;

        errno = 0;
        long level = strtol(level_str, &end, 10);
        int is_intger = (errno != ERANGE && *end == '\0');

        if (is_intger) {
            if (level == 3) { return STRICT_FLAGS; }
            else if (level == 2) { return MODERATE_FLAGS; }
            else if (level == 1) { return LINT_FLAGS; }
            else { return " "; }
        } else {
            LOG_WARN("You must pass an integer as argument for --strictness! Using defaults");
            return " ";
        }
    }
    
    return " ";
}

static bool is_compiler_valid(const char *str) {
    const char* const valid_compilers[] = { "gcc", "clang", "cl" };
    for (usize i = 0; i < 3; i++) {
        if (strncmp(str, valid_compilers[i], strlen(str)) == 0) {
            return true;
        }
    }

    return false;
}

static void set_strictness(const char **argv_p, CompilerOptions *opts) {
    char *level_str = strrchr(*argv_p, '=');
    if (level_str == NULL) {
        LOG_WARN("Couldn't parse the value for flag %s", *argv_p);
        return;
    }

    opts->strictness = (u8)atoi(++level_str);
    opts->strictness_set = true;
}

static void set_config(const char **argv_p, CompilerOptions *opts) {
    char *config = strrchr(*argv_p, '=');
    if (config == NULL) {
        LOG_WARN("Couldn't parse the value for flag %s", *argv_p);
        return;
    }

    to_lowercase(++config);
    opts->config = config;
    opts->config_set = true;
}

static void set_compiler(const char **argv_p, CompilerOptions *opts) {
    char *compiler = strrchr(*argv_p, '=');
    if (compiler == NULL) {
        LOG_WARN("Couldn't parse the value for flag %s", *argv_p);
        return;
    }

    if (!is_compiler_valid(++compiler)) {
        LOG_WARN("Invalid compiler '%s' provided, using system default", *compiler);

        #ifdef __GNUC__
        opts->compiler = "gcc";

        #elif defined(__clang__)
        opts->compiler = "clang";

        #else
        opts->compiler = "cl.exe";

        #endif
    } else {
        opts->compiler = compiler;
    }

    opts->compiler_set = true;
}

static void set_lang(const char **argv_p, CompilerOptions *opts) {
    char *lang = strrchr(*argv_p, '=');
    if (strlen(++lang) > 3) {
        LOG_WARN("Invalid --lang value '%s'", lang);
        return;
    }

    bool is_c = strncmp(lang, "c", 1);
    bool is_cpp = strncmp(lang, "c++", 3)
        || strncmp(lang, "cpp", 3)
        || strncmp(lang, "cxx", 3);

    if (!is_cpp && is_c) {
        opts->lang = "c";
        opts->lang_set = true;
    } else if (is_cpp) {
        opts->lang = "cpp";
        opts->lang_set = true;
    }
}

CompilerOptions* parse_compiler_flags(const int argc, const char **argv) {
    CompilerOptions *opts = calloc(1, sizeof(CompilerOptions));
    if (opts == NULL) {
        LOG_ERROR("Failed to allocate memory for CompilerOptions!");
        return NULL;
    }

    const char **argv_p = argv;
    while (*++argv_p != NULL) {
        if (strncmp(*argv_p, "--with-mimalloc", 15) == 0 && !opts->mimalloc_requested) {
            opts->mimalloc_requested = true;
        }

        if (strncmp(*argv_p, "--strictness=", 13) == 0 && !opts->strictness_set) {
            set_strictness(argv_p, opts);
        }

        if (strncmp(*argv_p, "--compiler=", 11) == 0 && !opts->compiler_set) {
            set_compiler(argv_p, opts);
        }

        if (strncmp(*argv_p, "--config=", 9) == 0 && !opts->config_set) {
            set_config(argv_p, opts);
        }

        if (strncmp(*argv_p, "--lang=", 7) == 0 && !opts->lang_set) {
            set_lang(argv_p, opts);
        }
    };

    LOG_INFO("We got %d args", argc);
    return opts;
}