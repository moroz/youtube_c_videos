#include <stdio.h>

#define THRESHOLD 80

void fold(char *line, size_t len);
void print_slice(char *line, size_t len);
int find_last_white(char *line);

int main() {
  char *line = NULL;
  size_t len, nread;

  while ((nread = getline(&line, &len, stdin)) != -1) {
    fold(line, nread);
  }
}

void fold(char *line, size_t len) {
  if (len < THRESHOLD + 1) {
    printf("%s", line);
    return;
  }

  int i, c, lastSpace;

  lastSpace = find_last_white(line);
  print_slice(line, lastSpace);
  fold(&line[lastSpace + 1], len - lastSpace);
}

int find_last_white(char *line) {
  int i, c;

  for (i = THRESHOLD; i >= 0; i--) {
    c = line[i];

    if (c == ' ' || c == '\t') {
      return i;
    }
  }

  return THRESHOLD;
}

void print_slice(char *line, size_t len) {
  for (int i = 0; i < len; i++) {
    putchar(line[i]);
  }
  putchar('\n');
}
