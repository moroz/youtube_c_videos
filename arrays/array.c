#include "array.h"

#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  return realloc(pointer, newSize);
}

void initArray(Array *array) {
  array->items = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeArray(Array *array, int64_t item) {
  if (array->capacity < array->count + 1) {
    size_t oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->items =
        GROW_ARRAY(int64_t, array->items, oldCapacity, array->capacity);
  }

  array->items[array->count] = item;
  array->count++;
}

void initProductArray(ProductArray *array) {
  array->items = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeProduct(ProductArray *array, Product item) {
  if (array->capacity < array->count + 1) {
    size_t oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->items =
        GROW_ARRAY(Product, array->items, oldCapacity, array->capacity);
  }

  array->items[array->count] = item;
  array->count++;
}
