#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define STACKSIZE 1000

typedef enum {
  TOKEN_LEFT_PAREN = '(',
  TOKEN_RIGHT_PAREN = ')',
  TOKEN_LEFT_BRACKET = '[',
  TOKEN_RIGHT_BRACKET = ']',
  TOKEN_LEFT_BRACE = '{',
  TOKEN_RIGHT_BRACE = '}',
} Token;

typedef struct {
  Token tokens[STACKSIZE];
  Token *stackTop;
} Stack;

void resetStack();
void push(Token token);
Token pop();
Token pair_for(Token token);
bool isToken(int c);

Stack stack;

int main() {
  int c, i;
  int line = 1;

  resetStack();

  while ((c = getchar()) != EOF) {
    if (isToken(c)) {
      push((Token)c);
    }

    if (c == '\n') {
      line++;
    }
  }

  for (Token *token = stack.tokens; token < stack.stackTop; token++) {
    printf("%c ", *token);
  }
}

Token pair_for(Token token) {
  switch (token) {
  case TOKEN_LEFT_PAREN:
    return TOKEN_RIGHT_PAREN;

  case TOKEN_RIGHT_PAREN:
    return TOKEN_LEFT_PAREN;

  case TOKEN_LEFT_BRACE:
    return TOKEN_RIGHT_BRACE;

  case TOKEN_RIGHT_BRACE:
    return TOKEN_LEFT_BRACE;

  case TOKEN_LEFT_BRACKET:
    return TOKEN_RIGHT_BRACKET;

  case TOKEN_RIGHT_BRACKET:
    return TOKEN_LEFT_BRACKET;
  }
}

bool isToken(int c) {
  return c == TOKEN_LEFT_BRACKET || c == TOKEN_RIGHT_BRACKET ||
         c == TOKEN_LEFT_BRACE || c == TOKEN_RIGHT_BRACE ||
         c == TOKEN_LEFT_PAREN || c == TOKEN_RIGHT_PAREN;
}

void push(Token token) {
  *stack.stackTop = token;
  stack.stackTop++;
}

Token pop() {
  stack.stackTop--;
  return *stack.stackTop;
}

void resetStack() { stack.stackTop = stack.tokens; }
