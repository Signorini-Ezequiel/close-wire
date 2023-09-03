#ifndef _HTTP_PROTOCOL
#define _HTTP_PROTOCOL
#include <stdlib.h>

struct http_header {
    char * name;
    char * value;
};

#define HTTP_REQUEST_TYPE_GET 0
#define HTTP_REQUEST_TYPE_POST 1

// Lectura de Headers con mayusculas
// "....." -> http_request (usar en el parser, incluir el http_example en la estructura para poderlo usar)
const char * http_example =
    "POST /mensaje HTTP/1.1\n"
    "Host: localhost:81\n"
    "User-Agent: Mozilla/5.0 (Windows) Firefox/52.1\n"
    "Accept: text/html\n"
    "Connection: keep-alive\n"
    "Content-Type: text/plain\n"
    "\n"
    "Hola, este es el mensaje!";

struct http_request {
    int request_type; // 'POST'
    char * request_context; // '/mensaje'
    struct http_header * headers; // '[{name: "Host", value: "google.com"}, ...]'
    size_t headers_length;  // cantidad de headers en el array
    unsigned char * content; // "Hola, este es el mensaje!"
    size_t content_length;
};

#endif
