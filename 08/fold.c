#include <stdio.h>

#define HARDSTOP 80

void empty_buffer(char *, size_t len);

int main() {
  int i, c;
  int wordstart = 0;
  int wordlength = 0;
  char word[HARDSTOP];

  i = 0;
  empty_buffer(word, HARDSTOP);

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      // if we are forced to break the line because the
      // last word stored in cache would overflow the line
      if (wordlength > 0 && (i + wordlength) > HARDSTOP) {
        putchar('\n');
        printf("%s", word);
        i = wordlength;
        wordlength = 0;
        continue;
      }

      printf("%s", word);
    } else {
      word[wordlength] = c;
      wordlength++;
    }

    putchar(c);
    ++i;

    if (i == HARDSTOP) {
      putchar('\n');
      i = 0;
    }

    if (c == '\n') {
      i = 0;
      empty_buffer(word, HARDSTOP);
    }
  }
}

void empty_buffer(char *buf, size_t len) {
  for (int i = 0; i < len; i++) {
    buf[i] = 0;
  }
}
