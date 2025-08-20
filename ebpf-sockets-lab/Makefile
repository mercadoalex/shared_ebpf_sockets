CC = clang
CFLAGS = -O2 -target bpf -c
LDFLAGS = -lelf -lz

GCC = gcc
GCCFLAGS = -O2

# Source files
EBPF_SRC = src/ebpf_program.c
EBPF_OBJ = $(EBPF_SRC:.c=.o)

LOADER_SRC = src/loader.c
LOADER_BIN = loader

# Default target
all: ebpf_program.o $(LOADER_BIN)

# Rule to build the eBPF program
ebpf_program.o: $(EBPF_SRC)
	$(CC) $(CFLAGS) $< -o $@

# Rule to build the loader
$(LOADER_BIN): $(LOADER_SRC) src/helpers.h
	$(GCC) $(GCCFLAGS) $< -o $@ $(LDFLAGS)

# Clean up build artifacts
clean:
	rm -f $(EBPF_OBJ) $(LOADER_BIN)

.PHONY: all clean