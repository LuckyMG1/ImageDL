#ifndef URL_PARSER_H
#define URL_PARSER_H

#include <stddef.h>

typedef struct {
	char hostname[256];
	char pathname[256];
	int port;
} url_t;

int parse_hostname(char * dest, char * source);
int parse_pathname(char * dest, char * source, int host_len);
int parse_url(url_t * dst_url, const char * source);

#endif
