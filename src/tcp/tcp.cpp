#include "tcp.h"

#include "client.h"
#include "server.h"

#include "../constants.h"
#include "../program.h"

#include <linux/ip.h>
#include <linux/tcp.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TCP_BUFFER_SIZE \
  (DEFAULT_PACKET_SIZE - sizeof(struct iphdr) - sizeof(struct tcphdr))

struct tcp_program_context {
  struct program_context context;
  pthread_mutex_t mutex;

  union {
    struct tcp_server server;
    struct tcp_client client;
  };
};

struct program_context* tcp_create_context(struct program* program) {
  struct tcp_program_context* context =
      malloc(sizeof(struct tcp_program_context));

  return (struct program_context*)context;
}

void tcp_free_context(struct program* program) {
  free(program->context);
}

void tcp_start_server(struct program* program) {
  struct tcp_program_context* context =
      (struct tcp_program_context*)program->context;

  struct tcp_server_start_options options = {
      .address = program->options.address,
      .port = program->options.port,
  };

  tcp_server_start(&context->server, &options);
}

void tcp_start_client(struct program* program) {
  struct tcp_program_context* context =
      (struct tcp_program_context*)program->context;

  tcp_client_start(&context->client);
}

struct mode_functions tcp_functions = {
    .start_server = tcp_start_server,
    .start_client = tcp_start_client,
    .create_context = tcp_create_context,
    .free_context = tcp_free_context,
};

struct mode mode_tcp = {
    .name = "tcp",
    .functions = &tcp_functions,
};
