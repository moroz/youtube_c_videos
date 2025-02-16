#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uchar.h>

void reverse_bytes(char str[], size_t len) {
  uint8_t buf;

  for (int i = 0, n = len / 2; i < n; i++) {
    buf = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = buf;
  }
}

void reverse_in_place(char str[]) {
  size_t len = strlen(str);
  uint8_t buf;

  reverse_bytes(str, len);

  for (int i = len - 1; i > 0; i--) {
    buf = str[i];

    // ASCII character, go ahead
    if (buf <= 0x7f) {
      continue;
    }

    // UTF8-2
    if (buf >= 0xC2 && buf <= 0xDF) {
      reverse_bytes(&str[i - 1], 2);
      i--;
      continue;
    }

    // UTF8-3
    if (buf >= 0xE0 && buf <= 0xEF) {
      reverse_bytes(&str[i - 2], 3);
      i -= 2;
      continue;
    }

    // UTF8-4
    if (buf >= 0xF0 && buf <= 0xF4) {
      reverse_bytes(&str[i - 3], 4);
      i -= 3;
    }
  }
}

int main() {
  char str[] = "Zażółć gęślą jaźń. こんにちは、先輩！And now some Emoji. "
               "Estonia: 🇪🇪 Iceland: 🇮🇸";

  reverse_in_place(str);

  printf("%s\n", str);
  return 0;
}
