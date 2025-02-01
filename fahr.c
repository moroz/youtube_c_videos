#include <stdio.h>
#include <stdint.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */
int main() {
	float fahr, celsius;
	int lower = 0, upper = 300, step = 5;

	printf("TEMPERATURE CONVERSION TABLE\n");
	celsius = lower;
	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius+32;
		printf("%6.1f\t%3.0f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
