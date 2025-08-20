// helpers.h
#ifndef HELPERS_H
#define HELPERS_H

#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

// Define constants for packet filtering
#define TCP_PROTOCOL 6
#define UDP_PROTOCOL 17

// Function prototypes for utility functions
void print_packet_info(const struct ethhdr *eth_hdr, const struct iphdr *ip_hdr);
int filter_tcp_packets(const struct iphdr *ip_hdr);
int filter_udp_packets(const struct iphdr *ip_hdr);

#endif // HELPERS_H