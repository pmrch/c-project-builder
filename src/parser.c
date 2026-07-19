#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "flags.h"
#include "utils.h"
#include "log.h"

#define COMPILER_FLAGS_SIZE 2048

static bool is_compiler_valid(const char *str) {
    const char* const valid_compilers[] = { "gcc", "clang", "cl" };
    for (usize i = 0; i < 3; i++) {
        if (strncmp(str, valid_compilers[i], strlen(valid_compilers[i])) == 0) {
            return true;
        }
    }

    return false;
}

static void set_strictness(char *restrict *argv_p, CompilerOptions *opts) {
    char *level_str = strrchr(*argv_p, '=');
    if (level_str == NULL) {
        LOG_WARN("Couldn't parse the value for flag %s", *argv_p);
        return;
    }

    opts->strictness = validate_strictness(++level_str);
    opts->strictness_set = true;
}

static void set_config(char *restrict *argv_p, CompilerOptions *opts) {
    char *config = strrchr(*argv_p, '=');
    if (config == NULL) {
        LOG_WARN("Couldn't parse the value for flag %s", *argv_p);
        return;
    }

    to_lowercase(++config);
    if (strncmp(config, "release", 7) == 0) { opts->config = Release; } 
    else if (strncmp(config, "debug", 5) == 0) { opts->config = Debug; } 
    else {
        LOG_WARN("Invalid config value '%s' provided, defaulting to Release build", config);
        opts->config = Release;
    }

    opts->config_set = true;
}

static void set_compiler(char *restrict *argv_p, CompilerOptions *opts) {
    char *compiler = strrchr(*argv_p, '=');
    if (compiler == NULL) {
        LOG_WARN("Couldn't parse the value for flag %s", *argv_p);
        return;
    }

    to_lowercase(++compiler);
    if (!is_compiler_valid(compiler)) {
        LOG_WARN("Invalid compiler '%s' provided, using system default", compiler);

        #ifdef __GNUC__
        opts->compiler = "gcc";

        #elif defined(__clang__)
        opts->compiler = "clang";

        #elif defined(_MSC_VER)
        opts->compiler = "cl.exe";

        #endif
    } else {
        opts->compiler = compiler;
    }

    opts->compiler_set = true;
}

static void set_lang(char *restrict *argv_p, CompilerOptions *opts) {
    char *lang = strrchr(*argv_p, '=');
    if (lang == NULL) {
        LOG_WARN("Couldn't parse the value for flag %s", *argv_p);
        return;
    }

    if (strlen(++lang) > 3) {
        LOG_WARN("Invalid --lang value '%s'", lang);
        return;
    }

    to_lowercase(lang);
    bool is_c = strcmp(lang, "c") == 0;
    bool is_cpp = strncmp(lang, "c++", 3) == 0
        || strncmp(lang, "cpp", 3) == 0
        || strncmp(lang, "cxx", 3) == 0;

    if (is_cpp) { opts->lang = Cpp; }
    else if (is_c) { opts->lang = C; }
    else {
        LOG_WARN("Neither C nor C++ was provided in any accepted form, defaulting to C");
        opts->lang = C;
    }

    opts->lang_set = true;
}

CompilerOptions* parse_compiler_flags(const int argc, const char *restrict *argv) {
    CompilerOptions *opts = calloc(1, sizeof(CompilerOptions));
    if (opts == NULL) {
        LOG_ERROR("Failed to allocate memory for CompilerOptions!");
        return NULL;
    }

    char **argv_p = clone_string_array_mutable(argv, (usize)argc);
    if (argv_p == NULL) {
        free(opts);
        return NULL;
    }

    while (*++argv_p != NULL) {
        strip_quotes(*argv_p);
        if (strncmp(*argv_p, "--with-system-mimalloc", 23) == 0 && !opts->use_system_mimalloc) {
            opts->use_system_mimalloc = true;
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