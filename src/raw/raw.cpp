#include "raw.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct raw_program_context {
  struct program_context context;
};

void raw_start_server(struct program* program) {
  printf("Starting raw socket server\n");
}

void raw_start_client(struct program* program) {
  printf("Starting raw socket client\n");
}

struct program_context* raw_create_context(struct program* program) {
  struct raw_program_context* context =
      malloc(sizeof(struct raw_program_context));

  return (struct program_context*)context;
}

void raw_free_context(struct program* program) {
  free(program->context);
}

struct mode_functions raw_functions = {
    .start_server = raw_start_server,
    .start_client = raw_start_client,
    .create_context = raw_create_context,
    .free_context = raw_free_context,
};

struct mode mode_raw = {
    .name = "raw",
    .functions = &raw_functions,
};
