#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_bytes(char *s, int len) {
  int n = len / 2;

  for (int i = 0; i < n; i++) {
    uint8_t c = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = c;
  }
}

void reverse(char *s) {
  size_t len = strlen(s);
  // Do not reverse the newline character if the given line
  // ends with one
  if (s[len - 1] == '\n') {
    len--;
  }

  reverse_bytes(s, len);

  for (int i = len - 1; i > 0; i--) {
    uint8_t c = s[i];

    // ASCII character, continue
    if (c <= 0x7F) {
      continue;
    }

    // UTF8-2
    if (c >= 0xC2 && c <= 0xDF) {
      reverse_bytes(&s[i - 1], 2);
      i--;
      continue;
    }

    // UTF8-3
    if (c >= 0xE0 && c <= 0xEF) {
      reverse_bytes(&s[i - 2], 3);
      i -= 2;
      continue;
    }

    if (c >= 0xF0 && c <= 0xF4) {
      reverse_bytes(&s[i - 3], 4);
      i -= 3;
    }
  }
}

int main() {
  char *line = NULL;
  size_t nread, len;

  while ((nread = getline(&line, &len, stdin)) != -1) {
    reverse(line);
    printf("%s", line);
  }

  free(line);
  // read lines
  // reverse input
  // ???
  // profit

  return 0;
}
