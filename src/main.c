#include "cli.h"
#include "program.h"

#include "raw/raw.h"
#include "tcp/tcp.h"
#include "zero_copy/zero_copy.h"

#include <e4c.h>
#include <stdio.h>

void start(int argc, char* argv[]) {
  struct program program = program_create();
  process_arguments(&program.options, argc, argv);

  program_register_mode(&program, &mode_tcp);
  program_register_mode(&program, &mode_raw);
  program_register_mode(&program, &mode_zero_copy);

  program_init_by_options(&program);

  program_start(&program);
}

int main(int argc, char* argv[]) {
  e4c_context_begin(false);

  int exit_code = 0;

  try {
    start(argc, argv);
  } catch (RuntimeException) {
    e4c_exception* exception = e4c_get_exception();
    fprintf(stderr, "%s", exception->message);
    exit_code = EXIT_FAILURE;
  }

  e4c_context_end();

  return exit_code;
}