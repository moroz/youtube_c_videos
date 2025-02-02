#include <stdio.h>

#define MAX_LENGTH 25
#define MAX_COUNT 40

typedef enum state_t {
  IN,
  OUT,
} state_t;

/* prints the lengths of words in file as a histogram */
int main() {
  int counts[MAX_LENGTH + 1];
  // Set default values for word counts from 1...MAX_LENGTH
  for (int i = 0; i <= MAX_LENGTH; i++) {
    counts[i] = 0;
  }

  // inside or outside a word
  state_t state = OUT;
  int c, currentCount = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == OUT) {
        continue;
      }

      state = OUT;
      // store the count of the last word
      if (currentCount == 0) {
        continue;
      }

      // cap the length of word at MAX_LENGTH
      if (currentCount > MAX_LENGTH) {
        currentCount = MAX_LENGTH;
      }

      counts[currentCount]++;
      currentCount = 0;
      continue;
    }

    state = IN;
    currentCount++;
  }

  for (int i = 1; i <= MAX_LENGTH; i++) {
    if (counts[i] == 0) {
      continue;
    }
    printf("%3d ", i);

    int width = counts[i];
    if (width > MAX_COUNT) {
      width = MAX_COUNT;
    }
    for (int i = 0; i < width; i++) {
      printf("█"); // Block
    }
    putchar('\n');
  }
}

/*
 * 1 #
 * 2 ###
 * 3
 *
 */
