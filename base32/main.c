#include "base32.h"
#include <stdio.h>
#include <string.h>

int main() {
  char *src = "Hello Base32!";
  char dst[80];
  base32_encode((uint8_t *)src, dst, strlen(src));

  printf("%s\n", dst);
}
