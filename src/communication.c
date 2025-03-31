#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#include "url_parser.h"
#include "communication.h"

char user_agent[USER_AGENT_SIZE];

// create an HTTP request with a designated user agent
int create_request(url_t * url, char req_buff[]) {
    char agent_str[] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36";
    strncpy(user_agent, agent_str, strlen(agent_str));
    sprintf(req_buff,
            "GET %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "User-Agent: %s\r\n"
            "Connection: close\r\n"
            "\r\n",
            url->pathname, url->hostname, user_agent);
    return 0;
}

// handle sending and receiving the request through socket
int handle_request(int sckt_id, char req_buff[], char recv_buff[]) {
    int recv_id, out_fd;
    // send request through socket
    if (send(sckt_id, req_buff, strlen(req_buff), 0) == -1) {
        perror("Could not send the request");
        return -1;
    }

    // open file for writing
    out_fd = open("out.png", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (out_fd == -1) {
        perror("Could not open file for writing");
        return -1;
    }

    // receive header
    int header = 1;
    char * header_end;
    while((recv_id = recv(sckt_id, recv_buff, RECV_SIZE, 0)) > 0) {
        if (header) {
            header_end = strstr(recv_buff, "\r\n\r\n");
            if (header_end) {
                header_end += 4;
                header = 0;
                write(out_fd, header_end, recv_id-(header_end-recv_buff));
            }
        } else {
            write(out_fd, recv_buff, recv_id);
        }
    }

    close(out_fd);
    return recv_id;
} 
