#include <time.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

int base32_decode(const char *src, unsigned char *dst);

int decode_hex(const char *hex, unsigned char *dst) {
  for (int i = 0, n = strlen(hex) / 2; i < n; i++) {
    unsigned int byte;
    sscanf(hex + 2 * i, "%02x", &byte);
    dst[i] = byte & 0xFF;
  }

  return 0;
}

void format_step(uint64_t step, uint8_t *dst) {
  for (int i = 0; i < 8; i++) {
    uint8_t byte = (step & 0xFFUL << ((7 - i) * 8)) >> ((7 - i) * 8);
    dst[i] = byte;
  }
}

long int unixepoch() {
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  return tp.tv_sec;
}

int main() {
  const char *key_base32 = "PHAD43OB23JAWG65LBKHQNHNTXHST66F";
  uint8_t key[20];
  uint8_t digest[16];
  base32_decode(key_base32, key);

  uint64_t t = unixepoch() / 30;
  uint8_t step_formatted[8];
  uint32_t len;
  format_step(t, step_formatted);
  HMAC(EVP_sha1(), key, 20, step_formatted, 8, digest, &len);

  int offset = digest[len - 1] & 0xF;
  int binary = ((digest[offset] & 0x7F) << 24) |
               ((digest[offset + 1] & 0xFF) << 16) |
               ((digest[offset + 2] & 0xFF) << 8) | (digest[offset + 3] & 0xFF);

  int otp = binary % 1000000;
  printf("%06d\n", otp);
}
