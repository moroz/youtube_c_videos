#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *dst, char *s);

int main() {
  char *line = NULL; /* line of input */
  char *rev = NULL;  /* buffer for the reversed line */
  size_t len, nread, bufsize;
  bufsize = 0;

  while ((nread = getline(&line, &len, stdin)) != -1) {
    if (len > bufsize) {
      rev = realloc(rev, len);
    }
    if (line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }
    reverse(rev, line);
    printf("%s\n", rev);
  }

  free(line);
  free(rev);

  return 0;
}

void reverse(char *dst, char *s) {
  size_t len = strlen(s);
  int i, c;

  for (i = 1; i <= len; i++) {
    c = s[len - i];
    dst[i - 1] = c;
  }

  dst[len] = '\0';
}
