#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "helpers.h"

#define PORT 8080

// Print packet/message contents in hex and ASCII
void print_packet(const char *data, ssize_t len) {
    printf("Packet content (%zd bytes):\n", len);
    for (ssize_t i = 0; i < len; i++) {
        printf("%02x ", (unsigned char)data[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\nASCII: ");
    for (ssize_t i = 0; i < len; i++) {
        char c = data[i];
        printf("%c", (c >= 32 && c <= 126) ? c : '.');
    }
    printf("\n");
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) ERROR_EXIT("socket");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        ERROR_EXIT("bind");

    if (listen(server_fd, 3) < 0) ERROR_EXIT("listen");
    printf("Packet Inspect Server listening on port %d...\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_fd < 0) ERROR_EXIT("accept");

    // Send a message to the client
    char *message = "Hello from Packet Inspect Server!\n";
    send(client_fd, message, strlen(message), 0);

    // Receive data from client and inspect
    char buffer[1024] = {0};
    ssize_t bytes_received = read(client_fd, buffer, sizeof(buffer));
    if (bytes_received > 0) {
        printf("Received data from client:\n");
        print_packet(buffer, bytes_received);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}