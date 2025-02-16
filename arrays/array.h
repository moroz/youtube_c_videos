#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdint.h>

void *reallocate(void *pointer, size_t newSize);

typedef struct {
  char *title;
  double basePrice;
} Product;

typedef struct {
  void *items;
  size_t count;
  size_t capacity;
} Array;

void initArray(Array *array);
void writeArray_int64(Array *array, int64_t item);
void writeArray_Product(Array *array, Product item);

#endif
