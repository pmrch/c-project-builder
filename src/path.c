#define PATH_MAX 1024

// Common imports
#include <string.h>

#include "log.h"
#include "path.h"
#include "utils.h"

// Support both Windows and Linux
#ifdef _MSC_VER
#include <direct.h>

// Returned buffer is malloc()'d by _getcwd(), so caller must free() it
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

// Returned buffer is malloc()'d by getcwd(), so caller must free() it
static char* get_cwd_linux() {
    char *buffer = malloc(PATH_MAX);
    if (buffer == NULL || getcwd(buffer, PATH_MAX) == NULL) {
        LOG_ERROR("Failed to get current working directory!");
        return NULL;
    }

    return buffer;
}

#endif

// Returned buffer is malloc()'d by the platform's compatible getcwd(), 
// so caller must free() it
char* get_cwd() {
    #ifdef _MSC_VER
    return get_cwd_win();
    
    #else
    return get_cwd_linux();

    #endif
}

// Returned buffer is strdup()'d, caller must free() it
char* get_basename(char *abs_path) {
    if (abs_path == NULL) {
        LOG_ERROR("NULL was provided instead of a valid path when getting filename!");
        return NULL;
    }

    #ifdef _MSC_VER
        char *last_slash = strrchr(abs_path, '\\');
    #else
        char *last_slash = strrchr(abs_path, '/');
        if (last_slash == NULL) {
            last_slash = strrchr(abs_path, '\\'); // MinGW fallback
        }
    #endif

    if (last_slash == NULL) {
        LOG_WARN("Returning path instead of filename, failed to extract it!");
    }

    return last_slash ? strdup_cross(++last_slash) : strdup_cross(abs_path);
}