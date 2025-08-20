#include "helpers.h"
#include <bpf/libbpf.h>
#include <stdio.h>

int main() {
    struct bpf_object *obj;
    int prog_fd;

    // Open the compiled eBPF object file
    obj = bpf_object__open_file("ebpf_program.o", NULL);
    if (!obj) ERROR_EXIT("bpf_object__open_file");

    // Load the eBPF program into the kernel
    if (bpf_object__load(obj)) ERROR_EXIT("bpf_object__load");

    // Get the file descriptor for the loaded program
    prog_fd = bpf_program__fd(bpf_object__find_program_by_name(obj, "bpf_sockops"));
    if (prog_fd < 0) ERROR_EXIT("bpf_program__fd");

    printf("eBPF program loaded and attached!\n");

    bpf_object__close(obj);
    return 0;
}