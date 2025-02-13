#include "uuid.h"
#include <stdio.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

static void debug_uuid(uuid_t uuid);

int64_t get_epoch_ms() {
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  return tp.tv_sec * 1000 + (tp.tv_nsec / 1000000);
}

UUIDv7Status generate_uuid_v7(UUIDv7Generator *gen, uint8_t dst[16]) {
  int64_t ms_ts = get_epoch_ms();
  uuid_t uuid;

  // If the last timestamp used by the generator was the same of greater
  // than the current timestamp, use next timestamp after the last one
  // (+ 1 millisecond)
  if (gen->last >= ms_ts) {
    ms_ts = gen->last + 1;
  }

  gen->last = ms_ts;

  // Put the most significant 6 bytes (48 bits)
  // of the millisecond timestamp in the first 6 bytes of the buffer
  // big-endian
  for (int i = 0; i < 6; i++) {
    // Take i-th byte from the end
    uint8_t byte = (ms_ts >> (i * 8)) & 0xFF;

    // Put it at the (5 - i)-th byte
    uuid[5 - i] = byte;
  }

  ssize_t rc = getrandom(&uuid[6], 10, 0);

  // If generating random bytes fails, fail the function
  if (rc == -1) {
    return UUID_ERR;
  }

  // The 4-bit version field as defined by Section 4.2, set to 0b0111 (7).
  // Occupies bits 48 through 51 of octet 6.
  uuid[6] = (uuid[6] & 0xF) | 0x70;

  // The 2-bit variant field as defined by Section 4.1, set to 0b10.
  // Occupies bits 64 and 65 of octet 8.
  uuid[8] = (uuid[8] & 0x3F) | (2 << 6);

  memcpy(dst, uuid, 16);

  return UUID_OK;
}

static void debug_uuid(uuid_t uuid) {
  for (int i = 0; i < 16; i++) {
    printf("%02x", uuid[i]);
    if (i == 4 || i == 6 || i == 8 || i == 10) {
      putchar('-');
    }
  }

  putchar('\n');
}
