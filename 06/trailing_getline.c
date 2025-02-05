#include <stdio.h>

int main() {
  size_t bufsize;
  char *line = NULL;
  size_t nread;
       
  while ((nread = getline(&line, &bufsize, stdin)) != -1) {
    int last_non_white = -1;
    for (int i = 0; i < nread; ++i) {
      char c = line[i];
      if (c != ' ' && c != '\t' && c != '\n') {
        last_non_white = i;
      }
    }

    if (last_non_white == -1) {
      continue;
    }

    for (int i = 0; i <= last_non_white; ++i) {
      putchar(line[i]);
    }
    putchar('\n');
  }

  return 0;
}
