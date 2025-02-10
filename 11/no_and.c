#include <stdio.h>

#define LINE_MAX 1000

int my_getline(char *dst, int limit);

int main() {
  char line[LINE_MAX];
  int len;

  while ((len = my_getline(line, LINE_MAX)) > 0) {
    printf("%s", line);
  }

  return 0;
}

int my_getline(char *dst, int limit) {
  int i = 0, c;

  while (i < limit - 1) {
    if ((c = getchar()) == '\n') {
      dst[i] = '\n';
      i++;
      break;
    }

    if (c == EOF) {
      break;
    }

    dst[i] = c;

    i++;
  }

  dst[i] = '\0';

  return i;
}
