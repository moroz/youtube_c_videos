#include "sqlite3.h"
#include "uuid.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

sqlite3 *mustConnect(const char *connString);

UUIDv7Generator uuidGen;

typedef struct Product {
  uuid_t ID;
  char *title;
  char *slug;
  char *description;
  double_t basePrice;
  time_t insertedAt;
  time_t updatedAt;
} Product;

int insertProduct(sqlite3 *db, Product product);

Product products[] = {
    {
        .title = "Steamed Hams",
        .slug = "steamed-hams",
        .description = "Two pieces of a bun with a beef patty inside.",
        .basePrice = 42.0,
    },
    {
        .title = "Cheeseburger",
        .slug = "cheeseburger",
        .description =
            "Same as a steamed ham, but with a slice of American cheese.",
        .basePrice = 48.0,
    }};

int main() {
  sqlite3 *db;
  int rc;

  db = mustConnect("./test.db");

  for (int i = 0; i < 2; i++) {
    rc = insertProduct(db, products[i]);
    printf("%d\n", rc);
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

static const char *insertProductSql =
    "insert into products (id, title, slug, description, base_price) values "
    "(?, ?, ?, ?, ?)";

int insertProduct(sqlite3 *db, Product product) {
  generate_uuid_v7(&uuidGen, product.ID);

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, insertProductSql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %d\n", rc);
    sqlite3_finalize(stmt);
    return rc;
  }

  sqlite3_bind_blob(stmt, 1, product.ID, 16, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, product.title, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, product.slug, -1, SQLITE_STATIC);
  if (product.description != NULL) {
    sqlite3_bind_text(stmt, 4, product.description, -1, SQLITE_STATIC);
  } else {
    sqlite3_bind_null(stmt, 4);
  }
  sqlite3_bind_double(stmt, 5, product.basePrice);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc;
}
