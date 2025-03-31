#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "socket_setup.h"

struct sockaddr_in * sckt_addr;
struct addrinfo * hints, * res;

int create_socket() { // HTTP SOCKET
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id == -1) {
        perror("There was an error creating the socket");
        return -1; // error
    }
    return socket_id; // success
}

int resolve_host(url_t * url) {
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_CANONNAME;
    if (getaddrinfo(url->hostname, NULL, hints, &res) == -1) {
        perror("The hostname could not be resolved");
        return -1; // error
    } 
    return 0; // success
}

int connect_to_host(url_t *url, struct addrinfo *res, int sckt_id)
{
    int connect_id;
    sckt_addr = (struct sockaddr_in *) res->ai_addr;
    sckt_addr->sin_port = htons(url->port);
    
    /*
     * printf("Connecting to: %s...\n", inet_ntoa(sckt_addr->sin_addr));
     * printf("Port: %hu\n", sckt_addr->sin_port);
     */
    connect_id = connect(sckt_id, (struct sockaddr *)sckt_addr, sizeof(*sckt_addr));
    if (connect_id == -1) {
        perror("Could not connect to the socket");
        return -1; // error
    }
    return connect_id; // success
}

