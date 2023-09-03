#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "net/driver.h"

int main(int argc, char ** argv) {

    const uint16_t port = 3321;
    
    union net_address address;
    memset(&address, 0, sizeof(address));
    struct net_open x = net_listen(0, &address, port, 6); // listen requests
    if (x.error) {
        printf("Ufa, dio error el net listen! 0x%x\n", x.error);
        return 1;
    }

    printf("Ya estoy escuchando lol! 0.0.0.0:%d\n", (int) port);
    while (1) {
        struct net_request req = net_accept(&x);
        if (!req.socket) {
            if (req.error) {
                printf("Ufa, no pude aceptar la petición...\n");
            } else {
                printf("Ufa, nadie me habla asi que voy a esperar...\n");
                usleep(100000);
            }
        } else {
            printf("Opa, hay request! Me llegó desde %d.%d.%d.%d:%d (%d)\n",
                (int) req.address.ipv4.raw.b1,
                (int) req.address.ipv4.raw.b2,
                (int) req.address.ipv4.raw.b3,
                (int) req.address.ipv4.raw.b4,
                (int) req.external_port, req.is_ipv6);
            static struct net_request_data result;
            memset(&result, 0, sizeof(result));
            int leido = net_read(&x, &req, &result);
            if (leido != 0) {
                printf("Ufa, no pude leer lo que me mandaron...\n");
                net_read_free(&x, &result);
            } else {
                printf("wowowowowow hay mensaje (%zu):\n%s\n", result.request_length, result.request_data);
                net_read_free(&x, &result);
                printf("Le voy a responder 'jaja'...\n");
                const char * mensaje = "jaja";
                net_send(&x, &req, mensaje, strlen(mensaje));
                net_close(&x, &req);
            }
        }
    }

    return 0;

}
