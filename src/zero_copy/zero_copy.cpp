#include "zero_copy.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct zero_copy_program_context {
  struct program_context context;
};

void start_server_zero_copy(struct program* program) {
  printf("Starting zero copy server\n");
}

void start_client_zero_copy(struct program* program) {
  printf("Starting zero copy client\n");
}

struct program_context* zero_copy_create_context(struct program* program) {
  struct zero_copy_program_context* context =
      malloc(sizeof(struct zero_copy_program_context));

  return (struct program_context*)context;
}

void zero_copy_free_context(struct program* program) {
  free(program->context);
}

struct mode_functions zero_copy_functions = {
    .start_server = start_server_zero_copy,
    .start_client = start_client_zero_copy,
    .create_context = zero_copy_create_context,
    .free_context = zero_copy_free_context,
};

struct mode mode_zero_copy = {
    .name = "zero_copy",
    .functions = &zero_copy_functions,
};