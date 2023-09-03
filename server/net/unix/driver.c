#include "../driver.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

struct net_open net_listen(int is_ipv6, union net_address * address, net_port port, unsigned int max_connections) {

    struct net_open ret = {0};

    int httpd_socket = socket(is_ipv6 ? PF_INET6 : PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (httpd_socket < 0) {
        ret.error = errno;
        return ret;
    }

    int bind_val;

    if (is_ipv6) {

        struct sockaddr_in6 name;
        memset(&name, 0, sizeof(name));

        name.sin6_port = htons(port);
        name.sin6_family = AF_INET6;
        name.sin6_addr.__in6_u.__u6_addr32[0] = address->ipv6.split.dw1;
        name.sin6_addr.__in6_u.__u6_addr32[1] = address->ipv6.split.dw2;
        name.sin6_addr.__in6_u.__u6_addr32[2] = address->ipv6.split.dw3;
        name.sin6_addr.__in6_u.__u6_addr32[3] = address->ipv6.split.dw4;

        int bind_val = bind(httpd_socket, (struct sockaddr *) &name, sizeof(name));

    } else {

        struct sockaddr_in name;
        memset(&name, 0, sizeof(name));

        name.sin_port = htons(port);
        name.sin_family = AF_INET;
        name.sin_addr.s_addr = address->ipv4.ip;

        int bind_val = bind(httpd_socket, (struct sockaddr *) &name, sizeof(name));

    }

    if (bind_val < 0) {
        ret.error = errno;
        close(httpd_socket);
        return ret;
    }

    int listen_val = listen(httpd_socket, max_connections);
    if (listen_val < 0) {
        ret.error = errno;
        close(httpd_socket);
        return ret;
    }

    ret.socket = httpd_socket;
    ret.is_ipv6 = is_ipv6;
    return ret;

}

struct net_request net_accept(struct net_open * net) {

    struct net_request req = {0};
    struct sockaddr_in6 client_name;
    unsigned int client_name_len = sizeof(client_name);
    int sock = accept(net->socket, (struct sockaddr *) &client_name, &client_name_len);

    if (sock < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return req;
        } else {
            req.error = errno;
            return req;
        }
    }

    req.socket = sock;
    if (client_name_len == sizeof(struct sockaddr_in6)) {
        req.external_port = client_name.sin6_port;
        req.address.ipv6.split.dw1 = client_name.sin6_addr.__in6_u.__u6_addr32[0];
        req.address.ipv6.split.dw2 = client_name.sin6_addr.__in6_u.__u6_addr32[1];
        req.address.ipv6.split.dw3 = client_name.sin6_addr.__in6_u.__u6_addr32[2];
        req.address.ipv6.split.dw4 = client_name.sin6_addr.__in6_u.__u6_addr32[3];
        req.is_ipv6 = 1;
    } else {
        struct sockaddr_in * client_name4 = (struct sockaddr_in *) &client_name;
        req.external_port = client_name4->sin_port;
        req.address.ipv4.ip = client_name4->sin_addr.s_addr;
    }

    return req;

}

int net_read(struct net_open * net, struct net_request * request, struct net_request_data * result) {
    const size_t bufsize = 1024 * 16;
    char * buffer = calloc(bufsize, 1);
    ssize_t read = recv(request->socket, buffer, bufsize, 0);
    if (read < 0) {
        return (int) read;
    } else {
        result->request_data = buffer;
        result->request_length = (size_t) read;
        return 0;
    }
}

void net_read_free(struct net_open * net, struct net_request_data * data) {
    if (data->request_data) {
        free(data->request_data);
    }
}

ssize_t net_send(struct net_open * net, struct net_request * request, const unsigned char * buffer, const size_t length) {
    return send(request->socket, buffer, length, 0);
}

void net_close(struct net_open * net, struct net_request * request) {
    if (request->socket) {
        close(request->socket);
        request->socket = 0;
    }
}

int net_stop(struct net_open * net) {
    if (net->socket != 0) {
        close(net->socket);
        net->socket = 0;
    }
}
