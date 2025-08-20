#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "helpers.h"

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char *msg = "Automated traffic packet\n";

    for (int i = 0; i < 100; i++) { // Send 100 packets/messages
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) ERROR_EXIT("socket");

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
            ERROR_EXIT("inet_pton");

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            ERROR_EXIT("connect");

        send(sock, msg, strlen(msg), 0);
        close(sock);

        usleep(100000); // Wait 100ms between packets
    }

    printf("Traffic generation complete.\n");
    return 0;
}