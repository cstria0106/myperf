#include "server.h"

#include <e4c.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

E4C_DEFINE_EXCEPTION(TcpServerException,
                     "Exception in TCP server",
                     RuntimeException);

void tcp_server_recv(struct tcp_server* server) {}

void tcp_server_accept(struct tcp_server* server) {}

void tcp_server_start(struct tcp_server* server,
                      struct tcp_server_start_options* options) {
  if (server->socket_fd > 0) {
    throw(TcpServerException, "TCP server is already started");
  }

  int socket_fd;

  try {
    // Socket initialization
    int socket_fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (socket_fd < 0) {
      throwf(TcpServerException, "Failed to create socket: %s",
             strerror(errno));
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = options->address;
    addr.sin_port = options->port;
    if (bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
      throwf(TcpServerException, "Failed to bind: %s", strerror(errno));
    }

    server->socket_fd = socket_fd;
    if (listen(socket_fd, 0) < 0) {
      throwf(TcpServerException, "Failed to listen: %s", strerror(errno));
    }

  } finally {
    if (socket_fd > 0) {
      close(socket_fd);
    }
  }
}