#include <stdio.h>

#define LOWER_LIMIT 32
#define UPPER_LIMIT 127

#define MAX_COUNT 40

int main() {
  int counts[UPPER_LIMIT - LOWER_LIMIT + 1];

  for (int i = LOWER_LIMIT; i <= UPPER_LIMIT; i++) {
    counts[i - LOWER_LIMIT] = 0;
  }

  int c;
  while ((c = getchar()) != EOF) {
    if (c < LOWER_LIMIT || c > UPPER_LIMIT) {
      continue;
    }

    counts[c - LOWER_LIMIT]++;
  }

  for (int i = LOWER_LIMIT; i <= UPPER_LIMIT; i++) {
    int count = counts[i - LOWER_LIMIT] > MAX_COUNT ? MAX_COUNT
                                                    : counts[i - LOWER_LIMIT];

    if (count == 0) {
      continue;
    }

    printf("%c ", i);
    for (int i = 0; i < count; i++) {
      printf("█");
    }
    putchar('\n');
  }
}
