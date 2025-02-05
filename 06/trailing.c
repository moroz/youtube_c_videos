#include <stdbool.h>
#include <stdio.h>

#define MAXLINE 1000 // buffer size

int getline_no_trailing(char *buf, int limit);

int main() {
  char line[MAXLINE];
  int len;

  while ((len = getline_no_trailing(line, MAXLINE)) > 0) {
    if (len > 1)
      printf("%s", line);
  }

  return 0;
}

int getline_no_trailing(char *buf, int limit) {
  int c, i;
  int last_non_white_index = -1;

  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    // if you encounter a space or tab, copy them to the buffer, but keep
    // track of the last non-white index
    if (c != ' ' && c != '\t') {
      last_non_white_index = i;
    }
    buf[i] = c;
  }
  // After we have read all the chars, revert to last
  // non-white index
  if (c == '\n') {
    i = last_non_white_index + 1;
    buf[i] = '\n';
    ++i;
    buf[i] = '\0';
  }

  return i;
}
