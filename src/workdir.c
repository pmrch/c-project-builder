#define PATH_MAX 1024

// Common imports
#include "log.h"

// Support both Windows and Linux
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>

static char* get_cwd_win() {
    char *buffer = _getcwd(NULL, PATH_MAX);
    if (buffer == NULL) {
        LOG_ERROR("Failed to get current working directory!");
        return NULL;
    }

    return buffer;
}

#else
#include <stdio.h>
#include <unistd.h>

static char* get_cwd_linux() {
    char *buffer = malloc(PATH_MAX);
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        LOG_ERROR("Failed to get current working directory!");
        return NULL;
    }

    return buffer;

}
#endif

char* get_cwd() {
    #if defined(_WIN32) || defined(_WIN64)
    return get_cwd_win();
    
    #else
    return get_cwd_linux();

    #endif
}