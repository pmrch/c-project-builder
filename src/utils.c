#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "utils.h"
#include "log.h"

#if _MSC_VER
#include <intrin.h>
#include <corecrt.h>
#include <stdbool.h>
#include <immintrin.h>

static void cpuid(i32 leaf, i32 subleaf, i32 out[4]) {
    __cpuidex(out, leaf, subleaf);
}

static CpuFeatures get_supported_isa() {
    CpuFeatures f = {0};
    i32 cpuInfo[4];

    // Get Leaf 1
    cpuid(1, 0, cpuInfo);
    f.sse2 = (cpuInfo[3] & (1 << 26)) != 0;

    bool osxsave = (cpuInfo[2] & (1 << 27)) != 0;
    bool avx     = (cpuInfo[2] & (1 << 28)) != 0;
    if (!(osxsave && avx)) { return f; }

    // OS support check for AVX registers
    usize xcr0 = _xgetbv(0);
    bool ymm_enabled = (xcr0 & 0x6) == 0x6;
    if (!ymm_enabled) { return f; }

    f.avx = true;

    // Get Leaf 7
    cpuid(7, 0, cpuInfo);
    if (cpuInfo[1] & (1 << 5)) { 
        f.avx2 = true; 
    }

    bool zmm_enabled = (xcr0 & 0xE6) == 0xE6;
    if (zmm_enabled && (cpuInfo[1] & (1 << 16))) {
        f.avx512f = true;
    }

    return f;
}

const char* get_best_isa() {
    CpuFeatures f = get_supported_isa();

    if (f.avx512f) return "/arch:AVX512";
    if (f.avx2)    return "/arch:AVX2";
    if (f.avx)     return "/arch:AVX";
    if (f.sse2)    return "/arch:SSE2";
    return "";
}
#endif

char *strdup_cross(const char *str) {
    #ifdef _MSC_VER
    return _strdup(str);
    
    #else
    return strdup(str);

    #endif
}

int strcat_cross(char *restrict dest, usize dest_size, const char *restrict src) {
    #ifdef _MSC_VER
    errno_t result = strcat_s(dest, dest_size, src);
    return (int)result;

    #else
    (void)dest_size;
    strcat(dest, src);
    return 0;

    #endif
}

// If a sequence of whitespace is found, they get reduced to a singular whitespace
void normalize_whitespaces(char *restrict s) {
    if (s == NULL) {
        LOG_WARN("Not normalizing whitespaces, passed NULL");
        return;
    }

    char *read_ptr  = s;
    char *write_ptr = s;
    u8   found_whitespace = 0;

    while (*read_ptr != '\0') {
        if (isspace(*read_ptr)) {
            if (++found_whitespace == 1) {
                *write_ptr++ = ' ';
            }
        } else {
            *write_ptr++ = *read_ptr;
            found_whitespace = 0;
        }

        read_ptr++;
    }

    *write_ptr = '\0';
}

void to_lowercase(char *restrict str) {
    if (str == NULL) {
        LOG_WARN("Cannot convert string to lowercase, NULL was passed");
        return;
    }

    while (*str != '\0') {
        *str = (char)tolower((i32)*str);
        ++str;
    }
}