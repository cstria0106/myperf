#include "program.h"

#include "constants.h"

#include <e4c.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

E4C_DEFINE_EXCEPTION(ProgramException,
                     "Exception in program",
                     RuntimeException);

void program_set_default_options(struct program_options* options) {
  options->list_modes = false;
  options->is_server = false;
  options->is_client = false;
  options->mode = DEFAULT_MODE;
  options->port = htons(DEFAULT_PORT);
}

struct program program_create() {
  struct program program;
  program_set_default_options(&program.options);
  TAILQ_INIT(&program.modes);
  return program;
}

void program_free(struct program* program) {
  program->context->mode->functions->free_context(program);
}

void program_register_mode(struct program* program, struct mode* mode) {
  TAILQ_INSERT_TAIL(&program->modes, mode, entries);
}

struct mode* find_mode_by_name(struct program* program, const char* name) {
  struct mode* mode;
  TAILQ_FOREACH(mode, &program->modes, entries) {
    if (strcmp(mode->name, name) == 0) {
      return mode;
    }
  }
  return NULL;
}

void program_init_by_options(struct program* program) {
  struct mode* mode = find_mode_by_name(program, program->options.mode);
  if (mode == NULL) {
    throwf(ProgramException, "%s is not valid mode", program->options.mode);
  }

  program->context = mode->functions->create_context(program);
  program->context->mode = mode;
}

void program_list_modes(struct program* program) {
  struct mode* mode;
  printf("Available modes:\n");
  TAILQ_FOREACH(mode, &program->modes, entries) {
    printf("    - %s\n", mode->name);
  }
}

void program_start(struct program* program) {
  struct program_options* options = &program->options;
  struct mode_functions* functions = program->context->mode->functions;

  if (options->list_modes) {
    program_list_modes(program);
  }

  if (options->is_server) {
    functions->start_server(program);
    return;
  }

  if (options->is_client) {
    functions->start_client(program);
    return;
  }

  throw(ProgramException,
        "Must either be a client (use -c option) or server (use -s option)");
}
