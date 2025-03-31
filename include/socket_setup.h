#ifndef SOCKET_SETUP_H
#define SOCKET_SETUP_H

#include <stddef.h>
#include <netdb.h>

#include "url_parser.h"

int create_socket();
int resolve_host(url_t * url);
int connect_to_host(url_t *url, struct addrinfo *res, int sckt_id);

#endif
