#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "helpers.h"

#define PORT 8080

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) ERROR_EXIT("socket");

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        ERROR_EXIT("bind");

    // Listen for connections
    if (listen(server_fd, 3) < 0) ERROR_EXIT("listen");
    printf("Server listening on port %d...\n", PORT);

    // Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_fd < 0) ERROR_EXIT("accept");

    // Send a message to the client
    char *message = "Hello from eBPF socket server!\n";
    send(client_fd, message, strlen(message), 0);

    // Clean up
    close(client_fd);
    close(server_fd);
    return 0;
}