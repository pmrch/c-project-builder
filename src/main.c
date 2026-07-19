#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "path.h"
#include "config.h"
#include "utils.h"
#include "build.h"
#include "parser.h"

static int is_arg(const char **argv) {
    int valid_prefix_kw = (argv[1][0] == '-' && argv[1][1] == '-');
    int is_path_win = (isalpha(argv[1][0]) && argv[1][1] == ':' && argv[1][2] == '\\');
    int is_path_linux = (argv[1][0] == '/');

    return valid_prefix_kw || is_path_win || is_path_linux;
}

int main(int argc, const char **argv) {
    CompilerConfig *cfg = new_config("compile_project");
    if (cfg == NULL) { return -1; }

    char *cwd = get_cwd();
    if (cwd == NULL) { goto cleanup; return -1; }

    if (argc > 1 && !is_arg(argv)) {
        printf("Invalid argument \"%s\" was passed!\n", argv[1]);
        goto cleanup;
    }

    ya();
    CompilerOptions *opts = parse_compiler_flags(argc, argv);
    printf("Set lang: %d | Set compiler: %d | Set config: %d | Set trictness: %d", 
        opts->lang_set, opts->compiler_set, opts->config_set, opts->strictness_set
    );

    goto cleanup;
    cleanup:
        free_compiler_config(cfg);
        free(cwd);
        return 0;
}