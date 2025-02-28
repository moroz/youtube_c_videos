#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int base32_decode(const char *src, unsigned char *dst);

void format_step(uint64_t step, uint8_t *dst) {
  for (int i = 0; i < 8; i++) {
    dst[i] = (step >> (7 - i) * 8) & 0xFF;
  }
}

long int unixepoch() {
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  return tp.tv_sec;
}

int main() {
  const char *key_base32 = "VXYLMUZAMMRWT5LFWBVDXCLYPJAMPZ5A";
  uint8_t key[20];
  uint8_t digest[20];
  base32_decode(key_base32, key);
  for (int i = 0; i < 20; i++) {
    printf("%02X ", key[i]);
  }
  putchar('\n');

  uint64_t t = unixepoch() / 30;
  uint8_t step_formatted[8];
  uint32_t len;
  format_step(t, step_formatted);
  HMAC(EVP_sha1(), key, 20, step_formatted, 8, digest, &len);

  for (int i = 0; i < 20; i++) {
    printf("%02X ", digest[i]);
  }
  putchar('\n');

  int offset = digest[len - 1] & 0xF;
  int binary = ((digest[offset] & 0x7F) << 24) |
               ((digest[offset + 1] & 0xFF) << 16) |
               ((digest[offset + 2] & 0xFF) << 8) | (digest[offset + 3] & 0xFF);

  int otp = binary % 1000000;
  printf("%06d\n", otp);

  return 0;
}
