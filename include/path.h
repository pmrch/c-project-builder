#ifndef PATH_H
#define PATH_H

#include "config.h"

// Returned buffer is malloc()'d by the platform's compatible getcwd(),
// so caller must free() it
char* get_cwd();

// Returned buffer is strdup()'d, caller must free() it
char* get_basename(char *abs_path);

// On Unix-based systems tries linking -lmimalloc with compiler.
// On Windows dynamically tries detecting if there is an available mimalloc DLL
bool is_mimalloc_available(CompilerConfig *cfg, char *restrict out);

#endif