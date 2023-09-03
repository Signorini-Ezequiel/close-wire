#ifndef _NET_DEFS
#define _NET_DEFS
#include <stdlib.h>
#include <stdint.h>

union net_address {
    union {
        struct {
            unsigned char b1;
            unsigned char b2;
            unsigned char b3;
            unsigned char b4;
        } raw;
        uint32_t ip;
    } ipv4;
    union {
        struct {
            unsigned char b1;
            unsigned char b2;
            unsigned char b3;
            unsigned char b4;
            unsigned char b5;
            unsigned char b6;
            unsigned char b7;
            unsigned char b8;
            unsigned char b9;
            unsigned char b10;
            unsigned char b11;
            unsigned char b12;
            unsigned char b13;
            unsigned char b14;
            unsigned char b15;
            unsigned char b16;
        } raw;
        struct {
            uint32_t dw1;
            uint32_t dw2;
            uint32_t dw3;
            uint32_t dw4;
        } split;
    } ipv6;
};

typedef uint16_t net_port;

struct net_request {
    int socket;
    int error;
    int is_ipv6;
    union net_address address;
    net_port external_port;
};

struct net_request_data {
    unsigned char * request_data;
    size_t request_length;
};

// stack
struct net_open {
    int error;
    int socket;
    int is_ipv6;
};

#endif
