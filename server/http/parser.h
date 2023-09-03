#ifndef _HTTP_PARSER  // si no esta definido (if not defined) lo define
#define _HTTP_PARSER
#include "protocol.h"
#include "../net/defs.h"

#define HTTP_PARSE_OK 0
#define HTTP_PARSE_ERROR_INVALID_TYPE 1

// retorna un posible codigo que represente un error, retorna el 1 en caso de error, por ahora si no es get o post
//              punto en que se guarda la info estructurada    content de la requestque llega
int http_parse(struct http_request * structured_request, struct net_request_data * request_data); // guarda memoria para la request (sin incluir el pointer dado)
void http_free(struct http_request * request); // libera dicha memoria (incluyendo el pointer de la request)

#endif
