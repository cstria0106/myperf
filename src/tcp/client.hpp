#ifndef TCP__CLIENT_H
#define TCP__CLIENT_H

struct tcp_client {
  int socket_fd;
};

void tcp_client_start(struct tcp_client* client);

#endif