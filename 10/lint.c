#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 256

typedef enum {
  TOKEN_LEFT_PAREN = '(',
  TOKEN_RIGHT_PAREN = ')',
  TOKEN_LEFT_BRACKET = '[',
  TOKEN_RIGHT_BRACKET = ']',
  TOKEN_LEFT_BRACE = '{',
  TOKEN_RIGHT_BRACE = '}',
  TOKEN_ERROR = -1,
} Token;

typedef struct Stack {
  Token stack[STACK_MAX];
  Token *stackTop;
} Stack;

Stack stack;

static void resetStack();
void push(Token token);
Token pop();
Token matchingToken(Token token);
void Fatalf(const char *error, ...);

int main() {
  int c;
  Token previous;

  resetStack();

  while ((c = getchar()) != EOF) {
    switch (c) {
    case TOKEN_LEFT_BRACE:
    case TOKEN_LEFT_BRACKET:
    case TOKEN_LEFT_PAREN:
      push(c);
      break;

    case TOKEN_RIGHT_BRACE:
    case TOKEN_RIGHT_BRACKET:
    case TOKEN_RIGHT_PAREN:
      previous = pop();
      if (previous != matchingToken(c)) {
        Fatalf(
            "unmatched token %c, expected the last token on the stack to be %c",
            c, matchingToken(c));
      }
      break;
    }
  }

  return 0;
}

static void resetStack() { stack.stackTop = stack.stack; }

void push(Token token) {
  *stack.stackTop = token;
  stack.stackTop++;
}

Token pop() {
  if (stack.stackTop == stack.stack) {
    return TOKEN_ERROR;
  }

  stack.stackTop--;
  return *stack.stackTop;
}

Token matchingToken(Token token) {
  switch (token) {
  case TOKEN_RIGHT_PAREN:
    return TOKEN_LEFT_PAREN;

  case TOKEN_RIGHT_BRACKET:
    return TOKEN_RIGHT_BRACKET;

  case TOKEN_RIGHT_BRACE:
    return TOKEN_LEFT_BRACE;

  default:
    return TOKEN_ERROR;
  }
}

void Fatalf(const char *error, ...) {
  va_list args;
  va_start(args, error);
  vfprintf(stderr, error, args);
  va_end(args);
  exit(1);
}
