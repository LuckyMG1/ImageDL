#include "url_parser.h"

int parse_hostname(char * dest, char * source) {
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

int parse_filename(char * dest, char * source, int host_len) {
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
