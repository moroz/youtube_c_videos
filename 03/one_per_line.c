#include <stdio.h>

typedef enum state_t {
	IN,
	OUT
} state_t;

int main() {
	state_t state = OUT;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN) {
				state = OUT;
				putchar('\n');
			}
			continue;
		}
		state = IN;
		putchar(c);
	}
}
