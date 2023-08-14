#include "cli.h"

#include "constants.h"
#include "program.h"
#include "util.h"

#include <arpa/inet.h>
#include <e4c.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

E4C_DEFINE_EXCEPTION(InvalidArgumentException,
                     "Invalid argument",
                     RuntimeException);

void show_help(char* executable_name, bool simple) {
  printf("Usage: %s [-s|-c host] [options]\n", executable_name);
  if (!simple) {
    printf("\n");
    printf("Additional help:\n");
    printf("    -m, --mode   <mode>     Select mode\n");
    printf("    -l, --list              List modes\n");
    printf("    -s, --server <address>  Start server bind to address\n");
    printf("    -c, --client <address>  Start client connect to address\n");
    printf("    -p, --port   <port>     Use custom port (default: %d)\n",
           DEFAULT_PORT);
  }
}

char* next(char*** argv) {
  char* temp = **argv;
  (*argv)++;
  return temp;
}

void process_arguments(struct program_options* options,
                       int argc,
                       char* argv[]) {
  options->executable_name = next(&argv);

  // If no option
  if (*argv == NULL) {
    show_help(options->executable_name, true);
    throw(InvalidArgumentException, "No argument is given");
  }

  while (*argv != NULL) {
    char* option = next(&argv);

    if (str_eq(option, "-h", "--help", NULL)) {
      show_help(options->executable_name, false);
      exit(0);
    }

    if (str_eq(option, "-c", "--client", "-s", "--server", NULL)) {
      options->is_client = str_eq(option, "-c", "--client", NULL);
      options->is_server = !options->is_client;

      char* address = next(&argv);
      if (address == NULL) {
        throwf(InvalidArgumentException, "%s option requires an address",
               option);
      }
      if (inet_pton(AF_INET, address, &options->address) != 1) {
        throwf(InvalidArgumentException, "'%s' is not valid address", address);
      }
      continue;
    }

    if (str_eq(option, "-p", "--port", NULL)) {
      char* port = next(&argv);
      if (port == NULL) {
        throwf(InvalidArgumentException, "%s option requires a port number",
               option);
      }

      char* port_end_ptr;
      long port_number = strtol(port, &port_end_ptr, 10);
      if (*port_end_ptr != '\0') {
        throwf(InvalidArgumentException, "'%s' is not valid port", port);
      }

      if (port_number <= 0 || port_number > USHRT_MAX) {
        throw(InvalidArgumentException,
              "Port number must be between 1 and 65535 inclusive");
      }

      options->port = (short)port_number;
      continue;
    }

    if (str_eq(option, "-m", "--mode", NULL)) {
      char* mode = next(&argv);
      if (mode == NULL) {
        throwf(InvalidArgumentException, "%s option requires a mode type",
               option);
      }
      options->mode = mode;
      continue;
    }

    if (str_eq(option, "-l", "--list", NULL)) {
      options->list_modes = true;
      continue;
    }

    throwf(InvalidArgumentException, "Unknown option %s", option);
  }
}
