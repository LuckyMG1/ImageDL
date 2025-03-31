#ifndef SOCKET_SETUP_H
#define SOCKET_SETUP_H

#include <stddef.h>
#include <netdb.h>

#include "url_parser.h"

int create_socket();
int resolve_host(url_t * url);
int connect_to_host(int sckt_id, url_t * url);

#endif
