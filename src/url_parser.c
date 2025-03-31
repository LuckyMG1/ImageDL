#include <stdio.h>
#include <string.h>

#include "url_parser.h"

char hostname_buff[256], pathname_buff[256];
int host_len, path_len;

int parse_hostname(char * dest, const char * source) {
    char * ch = (char *) source;
    int len = 0;
    // skip over protocol
    while (*ch != '\0' && *ch != ':') ch++;
    ch += 3; // skips '//'
    
    // read host until '/'
    if (*ch == '\0') return -1;
    while (*ch != '/') {
        dest[len++] = *(ch++);
    }
    dest[len] = '\0';
    return len;
}

int parse_pathname(char * dest, const char * source, int host_len) {
    int len = 0;
    char * ch = (char *) source;
    while (*ch != ':') {
        ch++;
    }
    ch += 3 + host_len;
    while (*ch != '\0')
        dest[len++] = *(ch++);
    dest[len] = '\0';
    return len;
}

int parse_url(url_t * dst_url, const char * url_string) {
    // get hostname and pathname from url_string
    host_len = parse_hostname(hostname_buff, url_string);
    if (host_len == -1) {
        perror("The hostname could not be parsed");
        return -1;
    }
     
    path_len = parse_pathname(pathname_buff, url_string, host_len); 
    if (path_len == -1) {
        perror("The path could not be paresd");
        return -1;
    }
    
    // zero out memory in url_t dst_url
    memset(dst_url->hostname, 0, sizeof(dst_url->hostname));
    memset(dst_url->pathname, 0, sizeof(dst_url->pathname));

    // safely copy buffers to respective fields
    strncpy(dst_url->hostname, hostname_buff, host_len);
    strncpy(dst_url->pathname, pathname_buff, path_len);
    
    dst_url->port = 80;
    
    return 0;  
}
