#ifndef PROGRAM_H
#define PROGRAM_H

#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/queue.h>

struct program;
struct program_context;

struct mode {
  const char* name;
  struct mode_functions* functions;

  TAILQ_ENTRY(mode) entries;
};

struct mode_functions {
  struct program_context* (*create_context)(struct program* program);
  void (*free_context)(struct program* program);
  void (*start_server)(struct program* program);
  void (*start_client)(struct program* program);
};

struct program_options {
  char* executable_name;
  bool list_modes;
  bool is_server;
  bool is_client;
  uint32_t address;
  uint16_t port;
  const char* mode;
};

struct program_context {
  struct mode* mode;
};

struct program {
  struct program_options options;
  struct program_context* context;

  TAILQ_HEAD(modes, mode) modes;
};

struct program program_create();
void program_free(struct program* program);
void program_register_mode(struct program* program, struct mode* mode);
void program_init_by_options(struct program* program);
void program_start(struct program* program);

#endif