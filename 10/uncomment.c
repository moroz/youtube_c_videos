#include <stdio.h>

void consume_string_literal();
void consume_char_literal();
void consume_cpp_style_comment();
void consume_c_style_comment();

void this_is_just_for_testing() {
  printf("//");
  printf("/* this should not be replaced */");
}

/* uncomment:  remove comments from C source code */
int main() {
  // C++ style comment, the only meaningful text in this line
  int c; // C++ style comment after code in line

  /*
   * Iterate over each character in the source code
   */
  while ((c = getchar()) != EOF) {
    if (c == '"') {
      putchar(c);
      consume_string_literal();
      continue;
    }

    if (c == '\'') {
      putchar('\'');
      consume_char_literal();
      continue;
    }

    if (c == '/') {
      if ((c = getchar()) == '/') {
        consume_cpp_style_comment();
        continue;
      }

      /* c is currently at the next character from /, because we read it in
       * the previous if statement */
      if (c == '*') {
        consume_c_style_comment();
        continue;
      }

      putchar('/');
      putchar(c);
      continue;
    }

    putchar(c);
  }

  return 0;
}

void consume_string_literal() {
  int c;

  while ((c = getchar()) != EOF) {
    putchar(c);

    if (c == '\\') {
      if ((c = getchar()) == '"') {
        putchar(c);
        continue;
      }
    }

    if (c == '"') {
      break;
    }
  }
}

void consume_char_literal() {
  int c;

  while ((c = getchar()) != EOF) {
    putchar(c);

    if (c == '\\') {
      if ((c = getchar()) == '\'') {
        putchar(c);
        continue;
      }
    }

    if (c == '\'') {
      break;
    }
  }
}

void consume_cpp_style_comment() {
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      break;
    }
  }

  printf(" \n");
}

void consume_c_style_comment() {
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '*' && (c = getchar()) == '/') {
      break;
    }
  }

  putchar(' ');
}
