#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print longest input line */
int main() {
  char *line = NULL; /* current input line */
  char *longest = NULL;
  size_t len = 0, max = 0, nread = 0, bufsize = 0;

  while ((nread = getline(&line, &len, stdin)) != -1) {
    if (nread > max) {
      max = nread;
      if (len > bufsize) {
        longest = realloc(longest, len);
        bufsize = len;
      }
      strcpy(longest, line);
    }
  }
  free(line);

  if (max > 0) {
    printf("%ld\n %s", max, longest);
  }

  free(longest);
  return 0;
}
