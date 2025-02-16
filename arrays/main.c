#include "array.h"
#include "sqlite3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  sqlite3 *db;
  int rc;

  rc = sqlite3_open("./test.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to open database: %d\n", rc);
    sqlite3_close(db);
    exit(1);
  }

  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, "select title, base_price from products", -1,
                          &stmt, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %d\n", rc);
    sqlite3_close(db);
    exit(1);
  }

  Array arr;

  initArray(&arr);

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    Product product;

    char *buf = (char *)sqlite3_column_text(stmt, 0);
    int len = sqlite3_column_bytes(stmt, 0);
    product.title = malloc(len + 1);
    strcpy(product.title, buf);

    writeArray_Product(&arr, product);
  }

  for (int i = 0; i < arr.count; i++) {
    Product product = ((Product *)arr.items)[i];
    printf("%s\n", product.title);
  }

  return 0;
}
