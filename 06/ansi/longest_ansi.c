#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {
  int len;               /* current line length */
  int max;               /* maximum length seen so far */
  char line[MAXLINE];    /* current input line */
  char longest[MAXLINE]; /* longest line saved here */

  max = 0;
  while ((len = getline(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }
  if (max > 0) {
    printf("%d\n%s", max, longest);
  }
  return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim) {
  int c, i;

  // Iterate until you reach EOF or \n
  // If there is still space in the buffer, store the last character
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
  }

  // Happy path: We had enough space to store the whole string
  if (c == '\n') {
    s[i] = c;
    ++i;
    s[i] = '\0';
  } else if (c != EOF) {
    // Unhappy path: The line was too long for us to store the whole string
    // and newline
    for (; (c = getchar()) != EOF && c != '\n'; i++)
      ;
    ++i;
    s[lim - 2] = '\n';
    s[lim - 1] = '\0';
  }
  return i;
}

/* copy: copy `from` into `to`; assume to is big enough */
void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0') {
    i++;
  }
}
