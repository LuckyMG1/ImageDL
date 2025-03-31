#include <stdio.h>
#include <errno.h>

#include "url_parser.h"
#include "socket_setup.h"
#include "communication.h"

int main(int argc, char * argv[]) {
    // declare variables
    url_t url;
    int sckt_id, cnct_id;
    char req_buff[REQ_SIZE], recv_buff[RECV_SIZE];
    
    // check correct num arguments
    if (argc != 2) {
        errno = EINVAL;
        perror("Usage is: image-dl <img-url>");
        return -1;
    }
    
    // construct url_t based on the &url string
    if (parse_url(&url, argv[1]) == -1) {
        return -1; // error handling alr done
    }
    
    // create socket and resolve the host ip
    sckt_id = create_socket(); 
    if (sckt_id == -1) return -1;
    if (resolve_host(&url) == -1) return -1;
    
    // establish connection to the server through socket
    cnct_id = connect_to_host(sckt_id, &url);
    if (cnct_id == -1) return -1;
    
    // create HTTP request & send it
    create_request(&url, req_buff);
    if (handle_request(sckt_id, req_buff, recv_buff) == -1)
        return -1;

    return 0;
}
