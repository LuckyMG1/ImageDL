#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

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

int main(int argc, char * argv[]) {
    int sckt_id, cnct_id, host_len;
    char hostname_buff[256], filename_buff[256], user_agent[128];
    char recv_buff[256], req_buff[512];
    struct sockaddr_in * sckt_addr;
    struct addrinfo hints, * res;
    
    if (argc != 2) {
        errno = EINVAL;
        perror("Usage is: image-dl <img-url>");
        return -1;
    }
    
    // parse hostname in argv
    if ((host_len = parse_hostname(hostname_buff, argv[1])) == -1) {
        perror("There was an error parsing the hostname");
        return -1;
    }
    
    // parse filename in argv
    if (parse_filename(filename_buff, argv[1], host_len) == -1) {
        perror("There was an error parsing the filename");
        return -1;
    }

    // create socket
    sckt_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sckt_id == -1) {
        perror("There was an error creating the socket");
        return -1;
    }
    
    // resolve host
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    if (getaddrinfo(hostname_buff, NULL, &hints, &res) == -1) {
        perror("There was an error resolving the hostname");
        return -1;
    }
    
    // connect to host
    sckt_addr = (struct sockaddr_in *)res->ai_addr;
    sckt_addr->sin_port = htons(443);
    printf("Connecting to: %s...\n", inet_ntoa(sckt_addr->sin_addr));
    printf("Port: %hu\n", sckt_addr->sin_port);
    cnct_id = connect(sckt_id, (struct sockaddr *)sckt_addr, sizeof(*sckt_addr));
    if (cnct_id == -1) {
        perror("There was an error connecting to the socket");
        return -1;
    }
    
    // create request
    strcpy(user_agent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36");
    sprintf(req_buff,
            "GET %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "User-Agent: %s\r\n"
            "Connection: close\r\n"
            "\r\n",
            filename_buff, hostname_buff, user_agent);

    // send request w/ user agent
    if (send(sckt_id, req_buff, strlen(req_buff), 0) == -1) {
        perror("There was an error sending the request");
        return -1;
    }

    // receive response
    if (recv(sckt_id, recv_buff, 256, 0) == -1) {
        perror("There was an error reading from the socket");
        return -1;
    }
    
    printf("%s\n", recv_buff);
    // connect socket to address
    /*
    cnct_id = connect(sckt_id, (struct sockaddr*)&sckt_addr, sizeof(sckt_addr)); 
    if (cnct_id == -1) {
        perror("There was an error binding to the socket");
        return -1;
    }
    */
    return 0;
}
