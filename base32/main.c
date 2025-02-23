#include "base32.h"
#include <stdio.h>
#include <string.h>

int main() {
  char *src = "Hello Base32!";
  uint8_t dst[80];
  base32_encode((uint8_t *)src, (char *)dst, strlen(src));
  printf("%s\n", dst);

  char *base32 = "KRSXG5BAIRSWG33ENFXGOIJBEE======";
  int n = base32_decode(base32, dst, 80);
  printf("%s\n", dst);
}
