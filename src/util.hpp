#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <stdbool.h>

// Allocate formatted string
char* vformat(const char* format, va_list args);
// Allocate formatted string
char* format(const char* format, ...);

bool str_eq(const char* source, ...);

#endif