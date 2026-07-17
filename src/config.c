#define MAX_VERSION 26
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "config.h"
#include "path.h"
#include "log.h"

static void cleanup_test() {
    remove("test");
    remove("test.c");
}

void free_compiler_config(CompilerConfig *cfg) {
    if (cfg->target != NULL) { free(cfg->target); }
    free(cfg);
}

#if !defined (_WIN32) && !defined (_WIN64)
static char* get_latest_std() {
    FILE *f = fopen("test.c", "w");
    fprintf(f, "int main() { return 0; }\n");
    fclose(f);

    unsigned int ref_size = sizeof("gcc -std=c23 -c test.c -o test > /dev/null 2>&1");
    unsigned int version = MAX_VERSION;

    char cmd[512];
    char *buf = malloc(4 * sizeof(char));

    while (version <= MAX_VERSION) {
        snprintf(cmd, ref_size, "gcc -std=c%u -c test.c -o test > /dev/null 2>&1", version);
        snprintf(buf, 4, "c%u", version);

        int res = system(cmd);
        if (res == 0) {
            cleanup_test();
            return buf;
        }

        version -= 3;
        sleep(1);
    }

    free(buf);
    cleanup_test();
    return NULL;
}
#endif

CompilerConfig* new_config(const char *project_name) {
    CompilerConfig *cfg_base = malloc(sizeof(CompilerConfig));
    if (cfg_base == NULL) {
        LOG_ERROR("Failed to allocate memory for compiler config");
        return NULL;
    }

    if (project_name == NULL) {
        char *path = get_cwd();
        cfg_base->target = get_basename(path);
    } else { 
        cfg_base->target = strdup(project_name); 
    }

    #if defined(_WIN32) || defined(_WIN64)
    cfg_base->std = "clatest";
    cfg_base->cc = "cl.exe";
    cfg_base->link = "link.exe";

    return cfg_base;
    #endif

    char *std = get_latest_std();

    cfg_base->std = std ? std : "c99";
    cfg_base->cc = system("gcc --version >/dev/null 2>&1") == 0 ? "gcc" : "clang";
    cfg_base->link = NULL;

    return cfg_base;
}