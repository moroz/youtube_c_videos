#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  sqlite3 *db; // pointer to DB connection
  char *zErrMsg =
      NULL; // buffer to store error message returned by SQLite as a string
  int rc;   // return code (should be SQLITE_OK on correct execution)

  rc = sqlite3_open("./test.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }

  int result;
  sqlite3_stmt *stmt;

  rc = sqlite3_prepare_v2(db, "select 2 + 2;", -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %d\n", rc);
    sqlite3_close(db);
    exit(1);
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    result = sqlite3_column_int(stmt, 0);
    printf("%d\n", result);
  }

  sqlite3_finalize(stmt);

  sqlite3_close(db);
  return 0;
}
