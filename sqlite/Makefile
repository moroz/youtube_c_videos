sqlite.download:
	bash download.sh

sqlite: sqlite.download
	cc -c sqlite3.c -o sqlite3.o
	ar rcs libsqlite3.a sqlite3.o

test: test.c
	cc test.c libsqlite3.a -o test

db.init:
	sqlite3 test.db < init.sql
