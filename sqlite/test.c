#include "sqlite3.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

sqlite3 *mustConnect(const char *connString);
sqlite3_stmt *mustPrepare(sqlite3 *db, const char *sql);

typedef struct Product {
  int ID;
  uint8_t *title;
  uint8_t *slug;
  uint8_t *description;
  double basePrice;
  time_t insertedAt;
  time_t updatedAt;
} Product;

int main() {
  sqlite3 *db; // pointer to DB connection
  int rc;      // return code (should be SQLITE_OK on correct execution)

  db = mustConnect("./test.db");

  sqlite3_stmt *stmt =
      mustPrepare(db, "select id, title, slug, description, base_price, "
                      "inserted_at, updated_at from products limit 1;");

  Product product;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    product.ID = sqlite3_column_int(stmt, 0);
    product.title = (uint8_t *)sqlite3_column_text(stmt, 1);
    product.basePrice = sqlite3_column_double(stmt, 4);
    printf("%d. %s — $%.0f\n", product.ID, product.title, product.basePrice);
  }

  sqlite3_finalize(stmt);

  sqlite3_close(db);
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

sqlite3_stmt *mustPrepare(sqlite3 *db, const char *sql) {
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %d\n", rc);
    sqlite3_close(db);
    exit(1);
  }

  return stmt;
}
