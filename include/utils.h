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
char *strdup_cross(const char *str);

int strcat_cross(char *restrict dest, size_t dest_size, const char *restrict src);

#endif