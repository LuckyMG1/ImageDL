#include "url_parser.h"

char hostname_buff[256], filename_buff[256];
int host_len, path_len;

int parse_hostname(char * dest, const char * source) {
    char * ch = source;
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

int parse_pathname(char * dest, char * source, int host_len) {
    int len = 0;
    char * ch = source;
    while (*ch != ':') {
        ch++;
    }
    ch += 3 + host_len;
    while (*ch != '\0')
        dest[len++] = *(ch++);
    dest[len] = '\0';
    return len;
}

int parse_url(url_t * result, const char * url_string) {
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
    
    // zero out memory in url_t result
    memset(result->hostname, 0, sizeof(result->hostname));
    memset(result->pathname, 0, sizeof(result->pathname));

    // safely copy buffers to respective fields
    strncpy(result->hostname, hostname_buff, host_len);
    strncpy(result->pathname, pathname_buff, path_len);

    return 0;  
}
