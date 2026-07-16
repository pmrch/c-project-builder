#include <stdlib.h>

#include "config.h"
#include "log.h"

void free_compiler_config(CompilerConfig *cfg) {
    if (cfg->target != NULL) { free(cfg->target); }
    free(cfg);
}

CompilerConfig* new_config(const char *project_name) {
    CompilerConfig *cfg_base = malloc(sizeof(CompilerConfig));
    if (cfg_base == NULL) {
        LOG_ERROR("Failed to allocate memory for compiler config");
        return NULL;
    }

    if (project_name == NULL) {

    }

    #if defined(_WIN32) || defined(_WIN64)
    cfg_base->std = "clatest";
    cfg_base->cc = "cl.exe";
    cfg_base->link = "link.exe";

    return cfg_base;
    #endif


    cfg_base->cc = "gcc";
    cfg_base->link = NULL;

    return cfg_base;
}

#if !defined (_WIN32) && !defined (_WIN64)
//const char* 
#endif