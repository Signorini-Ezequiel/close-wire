#ifndef _NET_DRIVER
#define _NET_DRIVER
#include "defs.h"

struct net_open net_listen(int is_ipv6, union net_address * address, net_port port, unsigned int max_connections);
// non-blocking, if socket = 0, request not accepted
struct net_request net_accept(struct net_open * net);
// does not allocate buffer
ssize_t net_read(struct net_open * net, struct net_request * request, struct net_request_data * result, const size_t length);
size_t net_request_data_alloc(struct net_request_data * data, size_t capacity);
void net_request_data_free(struct net_request_data * data);
ssize_t net_send(struct net_open * net, struct net_request * request, const unsigned char * buffer, const size_t length);
void net_close(struct net_open * net, struct net_request * request);
int net_stop(struct net_open * net);

#endif
