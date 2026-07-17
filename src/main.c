#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "log.h"
#include "path.h"
#include "config.h"

const char* valid_flags[] = {
    "--strictness=", "--lang=", "--compiler=", "--with-mimalloc", "--release", "--debug"
};

/*static bool param_is_valid(const char** avail, const char* elem, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(avail[i], elem) == 0) {
            return true;
        }
    }

    return false;
}*/


int main(int argc, char **argv) {
    CompilerConfig *cfg = new_config("compile_project");
    if (cfg == NULL) { return -1; }

    char *cwd = get_cwd();
    if (cwd == NULL) { goto cleanup; return -1; }

    if (argc > 1 && (!isupper(argv[1][0]) || (argv[1][0] != '-' && argv[1][1] != '-'))) {
        printf("Invalid argument \"%s\" was passed!\n", argv[1]);
        goto cleanup;
    }

    goto cleanup;
    cleanup:
        free_compiler_config(cfg);
        free(cwd);
        return 0;
}