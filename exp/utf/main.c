#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse(char **dst, const char *src) {
  size_t len = strlen(src);
  *dst = malloc(len + 1);

  char *buf = &(*dst)[len - 1];
  for (int i = 0; i < len;) {
    uint8_t c;
    int len = 4;
    c = src[i];

    // UTF8-1 or ASCII
    if (c <= 0x7F) {
      len = 1;
    }

    // UTF8-2, 2 characters
    if (c >= 0xC2 && c <= 0xDF) {
      len = 2;
    }

    // UTF8-3, 3 characters
    if (c >= 0xE0 && c <= 0xEF) {
      len = 3;
    }

    for (int j = i + len - 1; j >= i; j--) {
      *(buf--) = src[j];
    }

    i += len;
  }

  return 0;
}

int main() {
  char *dst;
  char *src = "你好世界 Hello, world!";

  reverse(&dst, src);

  printf("%s\n", dst);
  return 0;
}
