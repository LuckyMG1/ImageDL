#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stddef.h>
#include "url_parser.h"

#define USER_AGENT_SIZE 128
#define RECV_SIZE 256
#define REQ_SIZE 512

int create_request(url_t * url, char req_buff[]);
int handle_request(int sckt_id, char req_buff[], char recv_buff[]);

#endif
