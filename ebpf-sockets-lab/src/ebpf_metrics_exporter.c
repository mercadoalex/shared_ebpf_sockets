/*
 * ebpf_metrics_exporter.c
 * Exports packet count metrics from eBPF to Prometheus via HTTP.
 * This example uses two counters (server and client) and exposes them with labels.
 * For real eBPF metrics, replace the counters with reads from eBPF maps.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 9100

// Simulated packet counts (replace with eBPF map reads in real use)
volatile int server_packet_count = 0;
volatile int client_packet_count = 0;

// HTTP response callback for Prometheus scrape
int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    // Prometheus metrics format with labels for server and client
    const char *metrics =
        "# HELP ebpf_packet_count Total packets seen by eBPF\n"
        "# TYPE ebpf_packet_count counter\n"
        "ebpf_packet_count{role=\"server\"} %d\n"
        "ebpf_packet_count{role=\"client\"} %d\n";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), metrics, server_packet_count, client_packet_count);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer),
        (void*)buffer, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    // Start HTTP server for Prometheus to scrape metrics
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, "Failed to start HTTP server\n");
        return 1;
    }

    printf("ebpf_metrics_exporter running on port %d\n", PORT);

    // Simulate packet count increase (replace with eBPF map polling in real use)
    while (1) {
        server_packet_count += 2; // Simulate server packets
        client_packet_count += 1; // Simulate client packets
        sleep(1);
    }

    MHD_stop_daemon(daemon);
    return 0;
}