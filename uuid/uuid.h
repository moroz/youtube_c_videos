#ifndef UUID_H
#define UUID_H

#include <stdint.h>

typedef struct UUIDv7Generator {
  int64_t last;
} UUIDv7Generator;

typedef enum {
  UUID_OK = 0,
  UUID_ERR = -1,
} UUIDv7Status;

int64_t get_epoch_ms();
typedef uint8_t uuid_t[16];

UUIDv7Status generate_uuid_v7(UUIDv7Generator *gen, uint8_t dst[16]);

#endif
