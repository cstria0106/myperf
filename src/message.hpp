#include <stdint.h>

enum message_type {
  MESSAGE_START_TEST,
  MESSAGE_STOP_TEST,
  MESSAGE_ERROR,
};

struct message_header {
  enum message_type type;
  uint32_t payload_length;
};
