# Compiler choice
CC = gcc

# Strict Flag Collection
# -Werror: Turn warnings into errors
# -Wpedantic: Reject everything that isn't ISO C
# -Wextra: The "extra" warnings often missed by -Wall
STRICT_FLAGS = -Wall -Wextra -Wpedantic -Werror -Wuninitialized -Wmaybe-uninitialized \
	-Wconversion -Wsign-conversion -Wcast-align -Wcast-qual -Wstrict-aliasing=2 -Wpointer-arith \
	-Warray-bounds -Wnull-dereference -Wmissing-prototypes -Wstrict-prototypes \
	-Wold-style-definition -Wredundant-decls -Wshadow -Wundef -Wformat=2 -Wformat-security \
	-Wwrite-strings -Wvla -Wdouble-promotion -Wfloat-equal -Wswitch-enum -Wswitch-default \
	-Wunused -Wunused-function -Wunused-variable -Wunused-parameter -Wduplicated-cond \
	-Wduplicated-branches -Wlogical-op -Wno-padded -Wno-declaration-after-statement 

# Combine with standard flags and optimization
CFLAGS = -std=c23 $(STRICT_FLAGS) -Iinclude -MMD -MP -flto -ffast-math -O3 -march=native

# Linker flags (for libraries)
LDFLAGS = -flto

# Target definition
SRC := $(shell find src -name '*.c')
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
TARGET = build_c_project

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

print-version:
	@$(CC) --version

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf compile_commands.json
	rm -rf build

all: compile_commands 

.PHONY: clean
.PHONY: compile_commands $(TARGET)
compile_commands:
	bear -- make