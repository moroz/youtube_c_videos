#include <stdio.h>

#define MAX_LENGTH 30
#define MAX_COUNT 25

typedef enum state_t {
  IN,
  OUT,
} state_t;

void count_words(int *counts, int max_length);
int max_count(int *counts, int max_length);
void print_graph(int *counts, int max_length);

/* prints the lengths of words in file as a histogram */
int main() {
  int counts[MAX_LENGTH + 1];
  count_words(counts, MAX_LENGTH);
  print_graph(counts, MAX_LENGTH);
}

void count_words(int *counts, int max_length) {
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
}

int max_count(int *counts, int max_length) {
  int max = 0;
  for (int i = 1; i <= max_length; i++) {
    if (counts[i] > max) {
      max = counts[i];
    }
  }
  if (max > MAX_COUNT) {
    return MAX_COUNT;
  }
  return max;
}

void print_graph(int *counts, int max_length) {
  int max_height = max_count(counts, max_length);

  // For each row, go down with step -1
  for (int y = max_height; y >= 1; y--) {
    for (int i = 1; i <= max_length; i++) {
      if (counts[i] == 0) {
        continue;
      }

      if (counts[i] >= y) {
        printf("███ "); // Block
      } else {
        printf("    ");
      }
    }
    putchar('\n');
  }

  for (int i = 1; i <= max_length; i++) {
    if (counts[i] == 0) {
      continue;
    }

    if (counts[i] == MAX_COUNT) {
      printf("%2d+ ", counts[i]);
    } else {
      printf("%2d  ", i);
    }
  }
  putchar('\n');
}
