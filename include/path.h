#ifndef PATH_H
#define PATH_H

// Returned buffer is malloc()'d by the platform's compatible getcwd(),
// so caller must free() it
char* get_cwd();

// Returned buffer is strdup()'d, caller must free() it
char* get_basename(char *abs_path);

#endif