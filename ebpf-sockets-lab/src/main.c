#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/socket.h>
#include <sys/socket.h>
#include <unistd.h>
#include "helpers.h"

// Function prototypes
int load_ebpf_program();
void setup_socket_filtering(int sockfd);

int main() {
    // Load the eBPF program into the kernel
    if (load_ebpf_program() < 0) {
        fprintf(stderr, "Failed to load eBPF program\n");
        return EXIT_FAILURE;
    }

    // Create a raw socket for packet filtering
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    // Set up socket filtering using the loaded eBPF program
    setup_socket_filtering(sockfd);

    // Main loop to receive packets
    while (1) {
        char buffer[2048];
        ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
        if (bytes_received < 0) {
            perror("recv");
            break;
        }

        // Process the received packet (this can be expanded)
        printf("Received %zd bytes\n", bytes_received);
    }

    // Clean up
    close(sockfd);
    return EXIT_SUCCESS;
}