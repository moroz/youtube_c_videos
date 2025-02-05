#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 50

int main() {
  size_t buflen;
  size_t nread;
  char *line = NULL;

  while ((nread = getline(&line, &buflen, stdin)) != -1) {
    if (nread >= THRESHOLD) {
      printf("%s", line);
    }
  }

  free(line);

  return 0;
}
