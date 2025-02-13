#include "product.h"
#include "memory.h"
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

void initProductArray(ProductArray *array) {
  array->capacity = 0;
  array->count = 0;
  array->items = NULL;
}

void writeProduct(ProductArray *array, Product product) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->items =
        GROW_ARRAY(Product, array->items, oldCapacity, array->capacity);
  }

  array->items[array->count] = product;
  array->count++;
}

void freeProductArray(ProductArray *array) {
  for (int i = 0; i < array->count; i++) {
    freeProduct(&array->items[i]);
  }

  free(array->items);
  initProductArray(array);
}

void freeProduct(Product *product) {
  free(product->title);
  free(product->slug);
  free(product->description);
}

static const char *listProductsSQL =
    "select id, title, slug, description, base_price, inserted_at, updated_at "
    "from products order by id";

int listProducts(sqlite3 *db, ProductArray *target) {
  freeProductArray(target);
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, listProductsSQL, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    exit(1);
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    Product product;
    memcpy(&product.ID, sqlite3_column_blob(stmt, 0), 16);

    char *buf = (char *)sqlite3_column_text(stmt, 1);
    product.title = malloc(sqlite3_column_bytes(stmt, 1) + 1);
    strcpy(product.title, buf);

    buf = (char *)sqlite3_column_text(stmt, 2);
    product.slug = malloc(sqlite3_column_bytes(stmt, 2) + 1);
    strcpy(product.slug, buf);

    product.description = NULL;
    buf = (char *)sqlite3_column_text(stmt, 3);
    if (buf != NULL) {
      product.description = malloc(sqlite3_column_bytes(stmt, 3) + 1);
      strcpy(product.description, buf);
    }

    writeProduct(target, product);
  }

  return sqlite3_finalize(stmt);

  return rc;
}
