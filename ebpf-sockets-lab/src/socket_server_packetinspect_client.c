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
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) ERROR_EXIT("socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        ERROR_EXIT("inet_pton");

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        ERROR_EXIT("connect");

    // Receive message from server and inspect
    int valread = read(sock, buffer, sizeof(buffer) - 1);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("Received from server: %s", buffer);
        print_packet(buffer, valread);
    }

    // Send a message to the server for inspection
    char *client_msg = "Hello from Packet Inspect Client!\n";
    send(sock, client_msg, strlen(client_msg), 0);

    close(sock);
    return 0;
}