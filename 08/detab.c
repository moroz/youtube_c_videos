#include <stdio.h>

#define TABSIZE 4

int main() {
  int i;       /* current column in line */
  int c;       /* current character */
  int nexttab; /* position of next tab stop */

  i = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      // calculate the distance from the next tab stop
      nexttab = (i + TABSIZE);
      nexttab = nexttab - (nexttab % TABSIZE);

      for (; i < nexttab; ++i) {
        putchar(' ');
      }

      continue;
    }
    putchar(c);
    ++i;
    if (c == '\n') {
      i = 0;
    }
  }
}
