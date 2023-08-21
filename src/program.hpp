#ifndef PROGRAM_H
#define PROGRAM_H

#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/queue.h>
#include <string>

struct ProgramContext {};

class Program {};

class Mode {
 private:
  const std::string name;

 protected:
  explicit Mode(const std::string name);

 public:
  virtual ProgramContext* CreateContext() = 0;
  virtual void StartServer(Program* program) = 0;
  virtual void StartClient() = 0;

  ~Mode() = default;

  Mode(const Mode&) = delete;
  Mode& operator=(const Mode&) = delete;
};

struct ProgramOptions {
  char* executable_name;
  bool list_modes;
  bool is_server;
  bool is_client;
  uint32_t address;
  uint16_t port;
  const char* mode;
};

class Program {
 private:
  struct ProgramOptions options_;
  struct program_context* context;

  TAILQ_HEAD(modes, mode) modes;
};

struct program program_create();
void program_free(struct program* program);
void program_register_mode(struct program* program, struct mode* mode);
void program_init_by_options(struct program* program);
void program_start(struct program* program);

#endif