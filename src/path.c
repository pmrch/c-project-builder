#include <string.h>
#define PATH_MAX 1024

// Common imports
#include "log.h"
#include "path.h"

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

#include <stdlib.h>
#include <unistd.h>

static char* get_cwd_linux() {
    char *buffer = malloc(PATH_MAX);
    if (buffer == NULL || getcwd(buffer, PATH_MAX) == NULL) {
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

char* get_basename(char *abs_path) {
    LOG_INFO("Getting filename for %s", abs_path);
    if (abs_path == NULL) {
        LOG_ERROR("NULL was provided instead of a valid path when getting filename!");
        return NULL;
    }

    #if defined(_WIN32) || defined(_WIN64)
        char *last_slash = strrchr(abs_path, '\\');
    
    #else
        char *last_slash = strrchr(abs_path, '/');
    #endif

    if (last_slash == NULL) {
        LOG_WARN("Returning path isntead of filename, failed to extract it!");
    }

    return last_slash ? last_slash + 1 : abs_path;
}