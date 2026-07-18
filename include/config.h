#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    const char *std;
    const char *cc;
    const char *link;
    char *target;
} CompilerConfig;

int populate_empty_config(CompilerConfig *cfg);
void free_compiler_config(CompilerConfig *cfg);
CompilerConfig* new_config(const char *project_name);

#endif