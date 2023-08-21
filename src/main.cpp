#include "cli.h"
#include "program.h"

#include "raw/raw.h"
#include "tcp/tcp.h"
#include "zero_copy/zero_copy.h"

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
  int exit_code = 0;

  start(argc, argv);

  return exit_code;
}