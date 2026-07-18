#ifdef __clang__
    #define STRICT_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wuninitialized -Wold-style-definition          \
        -Wsign-conversion -Wcast-align -Wcast-qual -Wstrict-aliasing=2 -Wpointer-arith -Warray-bounds      \
        -Wnull-dereference -Wmissing-prototypes -Wstrict-prototypes -Wconversion -Wredundant-decls -Wvla   \
        -Wshadow -Wundef -Wformat=2 -Wformat-security -Wwrite-strings -Wdouble-promotion -Wfloat-equal     \
        -Wswitch-enum -Wswitch-default -Wunused -Wunused-function -Wunused-variable -Wunused-parameter     \
        -Wlogical-op -Wno-padded -Wno-declaration-after-statement -Weverything -Wno-unknown-warning-option \
        -Wno-padded -Wno-disabled-macro-expansion"

    #define MODERATE_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wuninitialized -Wconversion \
        -Wsign-conversion -Wcast-align -Wstrict-aliasing=2 -Wmissing-prototypes -Wswitch-enum \
        -Wredundant-decls -Wshadow -Wundef -Wformat=2 -Wwrite-strings -Wstrict-prototypes"

    #define LINT_FLAGS "-Wall"
#elif defined(__GNUC__)
    #define STRICT_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wuninitialized -Wmaybe-uninitialized       \
        -Wconversion -Wsign-conversion -Wcast-align -Wcast-qual -Wstrict-aliasing=2 -Wpointer-arith    \
        -Warray-bounds -Wnull-dereference -Wmissing-prototypes -Wstrict-prototypes -Wwrite-strings     \
        -Wredundant-decls -Wshadow -Wundef -Wformat=2 -Wformat-security  -Wvla -Wold-style-definition  \
        -Wdouble-promotion -Wfloat-equal -Wswitch-enum -Wswitch-default -Wunused -Wunused-function    \
        -Wunused-variable -Wunused-parameter -Wduplicated-cond -Wduplicated-branches -Wlogical-op      \
        -Wno-padded -Wno-declaration-after-statement"
    
    #define MODERATE_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wuninitialized -Wconversion  \
        -Wsign-conversion -Wcast-align -Wstrict-aliasing=2 -Wmissing-prototypes -Wswitch-enum \
        -Wredundant-decls -Wshadow -Wundef -Wformat=2 -Wwrite-strings -Wstrict-prototypes"

    #define LINT_FLAGS "-Wall"
#else
    #define STRICT_FLAGS "/W4 /permissive- /w14456 /w14457 /w14668 /w14061 /w14062 /w14244 /w14242 /w14018"
    #define MODERATE_FLAGS "/W4 /permissive-"
    #define LINT_FLAGS "/W3"
#endif