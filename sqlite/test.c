#include "sqlite3.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

sqlite3 *mustConnect(const char *connString);
sqlite3_stmt *mustPrepare(sqlite3 *db, const char *sql);

int main() {
  sqlite3 *db; // pointer to DB connection
  char *zErrMsg =
      NULL; // buffer to store error message returned by SQLite as a string
  int rc;   // return code (should be SQLITE_OK on correct execution)

  db = mustConnect("./test.db");

  uint64_t result;
  sqlite3_stmt *stmt = mustPrepare(db, "select unixepoch();");

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    result = sqlite3_column_int64(stmt, 0);
    printf("%ld\n", result);
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
