#include "kimera/transport.h"

bool open_udp_client(SocketState* sock_state, State* state) {
    sock_state->server_in = (socket_in*)malloc(sizeof(socket_in));
    sock_state->client_in = (socket_in*)malloc(sizeof(socket_in));
    
    if ((sock_state->server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("[UDP_SOCKET] Couldn't open stream socket.\n");
        return false;
    }

    memset(sock_state->server_in, 0, sizeof(socket_in)); 
    memset(sock_state->client_in, 0, sizeof(socket_in)); 

    sock_state->server_in->sin_family = AF_INET; 
    sock_state->server_in->sin_addr.s_addr = INADDR_ANY; 
    sock_state->server_in->sin_port = htons(state->port); 

    int n = 1024 * 1024;
    if (setsockopt(sock_state->server_fd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n)) == -1) {
        printf("[UDP_SOCKET] Couldn't allocate bigger UDP buffer. This might result in problems.\n");
    }

    if (bind(sock_state->server_fd, (socket_t*)sock_state->server_in, sizeof(socket_in)) < 0) {
        printf("[UDP_SOCKET] Couldn't bind with server port.\n");
        return false;
    }

    sock_state->interf = UDP;
    return true;
}

bool open_udp_server(SocketState* sock_state, State* state) {
    sock_state->server_in = (socket_in*)malloc(sizeof(socket_in));

    if ((sock_state->server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("[UDP_SOCKET] Couldn't open stream socket.\n");
        return false;
    }

    memset(sock_state->server_in, 0, sizeof(socket_in));
 
    sock_state->server_in->sin_family = AF_INET; 
    sock_state->server_in->sin_port = htons(state->port);
    sock_state->server_in->sin_addr.s_addr = inet_addr(state->address); 

    sock_state->interf = UDP;
    return true;
}

void close_udp(SocketState* sock_state) {
    close(sock_state->client_fd);
    close(sock_state->server_fd);
    sock_state->interf = NONE;
}