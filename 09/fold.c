#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THRESHOLD 80

int main() {
  char *line = NULL;
  size_t len, start, end, lastSpace, nextStart;
  int c, i;

  while ((end = getline(&line, &len, stdin)) != -1) {
    start = 0;

    for (;;) {
      if (end - start <= THRESHOLD) {
        printf("%s", &line[start]);
        break;
      }

      lastSpace = -1;

      for (i = start + THRESHOLD; i > start; i--) {
        c = line[i];

        if (c == ' ' || c == '\t') {
          lastSpace = i;
          nextStart = lastSpace + 1;
          break;
        }
      }

      /* No white space found in section, break word */
      if (lastSpace == -1) {
        nextStart = lastSpace = start + THRESHOLD;
      }

      for (i = start; i < lastSpace; i++) {
        putchar(line[i]);
      }

      putchar('\n');

      start = nextStart;
    }
  }

  free(line);

  return 0;
}
