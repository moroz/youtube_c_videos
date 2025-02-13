#include "product.h"
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3 *mustConnect(const char *connString);

static void debug_uuid(uuid_t uuid) {
  for (int i = 0; i < 16; i++) {
    printf("%02x", uuid[i]);
    if (i == 4 || i == 6 || i == 8 || i == 10) {
      putchar('-');
    }
  }

  putchar('\n');
}

int main() {
  sqlite3 *db; // pointer to DB connection
  int rc;      // return code (should be SQLITE_OK on correct execution)

  db = mustConnect("./test.db");

  ProductArray products;

  listProducts(db, &products);

  for (int i = 0; i < products.count; i++) {
    Product product = products.items[i];
    debug_uuid(product.ID);
    printf("%s, %s\n%s\n", product.title, product.slug, product.description);
  }

  return 0;
}

sqlite3 *mustConnect(const char *connString) {
  sqlite3 *db;
  int rc = sqlite3_open(connString, &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }

  return db;
}
