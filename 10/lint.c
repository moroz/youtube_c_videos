#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Global variable to store global state -- stack of opening tokens
Stack stack;

static void resetStack();
void push(Token token);
Token pop();
Token matchingToken(Token token);
void Fatalf(const char *error, ...);

void consumeStringLiteral();
void consumeCharLiteral();
void consumeCppStyleComment();
void consumeCStyleComment();

int main() {
  int c, lastC;
  Token previous;

  lastC = 0;
  resetStack();

  while ((c = getchar()) != EOF) {
    switch (c) {
    case '"':
      consumeStringLiteral();
      break;

    case '\'':
      consumeCharLiteral();
      break;

    case '*':
      if (lastC == '/') {
        consumeCStyleComment();
      }
      break;

    case '/':
      if (lastC == '/') {
        consumeCppStyleComment();
      }
      break;

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
    lastC = c;
  }

  // If the stack is not empty, we have reach EOF without finding a closing
  // token
  if (stack.stackTop != stack.stack) {
    previous = pop();
    Fatalf("EOF reached without matching closing token %c for token %c",
           matchingToken(previous), previous);
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
    return TOKEN_LEFT_BRACKET;

  case TOKEN_RIGHT_BRACE:
    return TOKEN_LEFT_BRACE;

  case TOKEN_LEFT_BRACE:
    return TOKEN_RIGHT_BRACE;

  case TOKEN_LEFT_PAREN:
    return TOKEN_RIGHT_PAREN;

  case TOKEN_LEFT_BRACKET:
    return TOKEN_RIGHT_BRACKET;

  default:
    return TOKEN_ERROR;
  }
}

// basically Go's log.Fatalf, but without timestamp for now
void Fatalf(const char *error, ...) {
  va_list args;
  va_start(args, error);
  vfprintf(stderr, error, args);
  va_end(args);

  size_t len = strlen(error);
  if (error[len - 1] != '\n') {
    putchar('\n');
  }
  exit(1);
}

void consumeStringLiteral() {
  int c;

  while ((c = getchar()) != EOF && c != '\n') {
    // continue consumption on \" escape sequence
    if (c == '\\') {
      if ((c = getchar()) == '"') {
        continue;
      }
    }

    if (c == '"') {
      return;
    }
  }

  // no need to return -- Fatalf will call exit(1)
  if (c == '\n') {
    Fatalf("unterminated string literal meets newline");
  }

  Fatalf("unterminated string literal meets EOF");
}

void consumeCharLiteral() {
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\\') {
      if ((c = getchar()) == '\'') {
        continue;
      }
    }

    if (c == '\'') {
      break;
    }
  }
}

void consumeCppStyleComment() {
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      break;
    }
  }
}

void consumeCStyleComment() {
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '*' && (c = getchar()) == '/') {
      break;
    }
  }
}
