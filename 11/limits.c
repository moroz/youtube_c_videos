#include <float.h>
#include <limits.h>
#include <stdio.h>

int main() {
  printf("char:\t\tmin = %d,\t\t\tmax = %d\n", CHAR_MIN, CHAR_MAX);
  printf("short:\t\tmin = %d,\t\t\tmax = %d\n", SHRT_MIN, SHRT_MAX);
  printf("int:\t\tmin = %d,\t\tmax = %d\n", INT_MIN, INT_MAX);
  printf("long:\t\tmin = %ld,\tmax = %ld\n", LONG_MIN, LONG_MAX);

  printf("unsigned char:\tmin = %d,\t\t\tmax = %d\n", 0, UCHAR_MAX);
  printf("unsigned short:\tmin = %d,\t\t\tmax = %d\n", 0, USHRT_MAX);
  printf("unsigned int:\tmin = %d,\t\t\tmax = %ld\n", 0, UINT_MAX);
  printf("unsigned long:\tmin = %d,\t\t\tmax = %lu\n", 0, ULONG_MAX);

  printf("float: min = %f, max = %f\n", FLT_MIN, FLT_MAX);
  printf("double: min = %f, max = %f\n", DBL_MIN, DBL_MAX);

  return 0;
}
