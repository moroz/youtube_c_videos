#include <stdio.h>
#include <stdint.h>

int main() {
	uint32_t blanks = 0, tabs = 0, newlines = 0;

	int c;
	while ((c = getchar()) != EOF) {
		switch (c) {
			case '\n':
				newlines++;
				break;
			
			case '\t':
				tabs++;
				break;

			case ' ':
				blanks++;
				break;
		}
	}

	printf("Blanks: %u\n", blanks);
	printf("Tabs: %u\n", tabs);
	printf("Newlines: %u\n", newlines);
}
