#include "base32.h"
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SECRET "VXYLMUZAMMRWT5LFWBVDXCLYPJAMPZ5A"

static void debug_binary(uint8_t *buf, size_t len) {
  for (int i = 0; i < len; i++) {
    printf("%02X ", buf[i]);
  }

  putchar('\n');
}

static time_t unixepoch() {
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  return tp.tv_sec;
}

static void encode_time_step(uint64_t step, uint8_t *dst) {
  for (int i = 0; i < 8; i++) {
    dst[i] = (step >> (7 - i) * 8) & 0xFF;
  }
}

int main() {
  uint8_t key[20];
  base32_decode(SECRET, key, 20);

  uint64_t time_step = unixepoch() / 30;
  printf("%llu\n", time_step);

  uint8_t T[8];
  encode_time_step(time_step, T);
  debug_binary(T, 8);

  uint8_t digest[20];
  unsigned int len;
  HMAC(EVP_sha1(), key, 20, T, 8, digest, &len);

  debug_binary(digest, 20);

  int offset = digest[19] & 0xF;

  uint32_t binary = (digest[offset + 0] & 0x7F) << 24 |
                    digest[offset + 1] << 16 | digest[offset + 2] << 8 |
                    digest[offset + 3];

  int otp = binary % 1000000;
  printf("%06d\n", otp);

  return 0;
}
