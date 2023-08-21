#ifndef TCP__SERVER_H
#define TCP__SERVER_H

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>

struct tcp_server {
  int socket_fd;
  int connection_fd;
};

struct tcp_server_start_options {
  uint32_t address;  // in network byte order
  uint16_t port;     // in network byte order
};

void tcp_server_start(struct tcp_server* server,
                      struct tcp_server_start_options* options);

#endif