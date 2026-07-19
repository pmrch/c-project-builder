#ifndef UTILS_H
#define UTILS_H

// ===========================================
// =         Shared Included Headers         =
// ===========================================
#include <stddef.h>
#include <stdint.h>

// ===========================================
// =      Convenient Type Definitions        =
// ===========================================
typedef uint8_t   u8;
typedef uint32_t u32;

typedef int32_t  i32;
typedef size_t usize;

typedef enum : u8 {
    C   = 0,
    Cpp = 1,
} Lang;

typedef enum : u8 {
    Debug   = 0,
    Release = 1
} Config;

typedef enum : u8 {
    Lazy     = 0,
    Lint     = 1,
    Moderate = 2,
    Strict   = 3
} Strictness;

// ===========================================
// =        Windows CPU intrinsics           =
// ===========================================
#if defined(_WIN32) || defined(_WIN64)
#include <stdbool.h>

typedef struct CpuFeatures {
    bool sse2;
    bool avx;
    bool avx2;
    bool avx512f;
} CpuFeatures;

const char* get_best_isa();
#endif

// ===========================================
// =        General Shared Utility           =
// ===========================================

// If a sequence of whitespace is found, they get reduced to a singular whitespace
void normalize_whitespaces(char *restrict s);
void to_lowercase(char *restrict str);
void strip_quotes(char *restrict s);

char* strdup_cross(const char *str);
char** clone_string_array_mutable(const char *restrict *arr, usize num_elem);

int create_test_file();
int strcat_cross(char *restrict dest, size_t dest_size, const char *restrict src);

#endif