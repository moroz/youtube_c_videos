#include <stdio.h>

/* copy input to output; 2nd version */
int main() {
	int c;

	int equal;
	while ((equal = ((c = getchar()) != EOF))) {
		putchar(c);
	}
}
