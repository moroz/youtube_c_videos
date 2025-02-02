#include <stdio.h>
#include <stdbool.h>

int main() {
	int c;
	bool last_char_was_blank = false;

	while ((c = getchar()) != EOF) {
		if (c == ' ' && last_char_was_blank) {
			continue;
		}
		putchar(c);
		last_char_was_blank =      (c == ' ');
	}
}
