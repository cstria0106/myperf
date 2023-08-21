
#include "util.h"

#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* vformat(const char* format, va_list args) {
  va_list temp;
  va_copy(temp, args);
  size_t size = vsnprintf(NULL, 0, format, temp);
  char* string = malloc(size + 1);
  vsprintf(string, format, args);
  return string;
}

char* format(const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* string = vformat(format, args);
  va_end(args);
  return string;
}

bool str_eq(const char* source, ...) {
  va_list args;
  va_start(args, source);
  char* to_compare;
  while (true) {
    to_compare = va_arg(args, char*);
    if (to_compare == NULL)
      break;

    if (strcmp(source, to_compare) == 0)
      return true;
  }
  va_end(args);
  return false;
}
