#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "workdir.h"

int main(int argc, char **argv) {
    CompilerConfig *cfg = new_config("compile_project");
    if (cfg == NULL) { return -1; }

    char *cwd = get_cwd();
    if (cwd == NULL) { goto cleanup; return -1; }

    return 0;
    cleanup:
        free(cfg);
        free(cwd);
}