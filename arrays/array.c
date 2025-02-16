#include "array.h"

#include <stdlib.h>

void *reallocate(void *pointer, size_t newSize) {
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

#define MAYBE_GROW_ARRAY(type, array)                                          \
  do {                                                                         \
    if ((array)->capacity < (array)->count + 1) {                              \
      (array)->capacity = array->capacity < 8 ? 8 : array->capacity * 2;       \
      (array)->items = (type *)reallocate((array)->items,                      \
                                          sizeof(type) * (array)->capacity);   \
    }                                                                          \
  } while (0)

void writeArray_int64(Array *array, int64_t item) {
  MAYBE_GROW_ARRAY(int64_t, array);
  ((int64_t *)array->items)[array->count] = item;
  array->count++;
}

void writeArray_Product(Array *array, Product item) {
  MAYBE_GROW_ARRAY(Product, array);
  ((Product *)array->items)[array->count] = item;
  array->count++;
}

#undef MAYBE_GROW_ARRAY
