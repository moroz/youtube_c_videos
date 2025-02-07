#include <stdio.h>

#define TABSIZE 2

int main() {
  int i, c;
  int blanks;
  int desired_position;

  i = 0;
  desired_position = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      desired_position++;
      continue;
    }

    if (c == '\t') {
      desired_position += TABSIZE;
      desired_position -= (desired_position % TABSIZE);
      continue;
    }

    while (i < desired_position) {
      if (desired_position - i >= TABSIZE) {
        putchar('\t');
        i += TABSIZE;
        continue;
      }

      putchar(' ');
      i++;
    }

    putchar(c);
    i++;
    desired_position = i;

    if (c == '\n') {
      i = 0;
      blanks = 0;
      desired_position = 0;
    }
  }

  return 0;
}
