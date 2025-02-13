#ifndef PRODUCT_H
#define PRODUCT_H

#include "sqlite3.h"
#include "uuid.h"
#include <math.h>
#include <stdint.h>

typedef struct Product {
  uuid_t ID;
  char *title;
  char *slug;
  char *description;
  double_t basePrice;
  uint64_t insertedAt;
  uint64_t updatedAt;
} Product;

typedef struct {
  Product *items;
  int capacity;
  int count;
} ProductArray;

void initProductArray(ProductArray *array);
void writeProduct(ProductArray *array, Product product);
void freeProductArray(ProductArray *array);

void freeProduct(Product *product);

int listProducts(sqlite3 *db, ProductArray *target);

#endif
