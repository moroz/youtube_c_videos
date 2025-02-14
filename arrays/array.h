#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdint.h>

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount)                          \
  (type *)reallocate(pointer, sizeof(type) * (oldCount),                       \
                     sizeof(type) * (newCount))

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

typedef struct {
  char *title;
  double basePrice;
} Product;

typedef struct {
  int64_t *items;
  size_t count;
  size_t capacity;
} Array;

void initArray(Array *array);
void writeArray(Array *array, int64_t item);

typedef struct {
  Product *items;
  size_t count;
  size_t capacity;
} ProductArray;

void initProductArray(ProductArray *array);
void writeProduct(ProductArray *array, Product item);

#endif
