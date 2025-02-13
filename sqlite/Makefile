sqlite.download:
	bash download.sh

sqlite: sqlite.download
	cc -c sqlite3.c -o sqlite3.o
	ar rcs libsqlite3.a sqlite3.o

test: test.c
	cc test.c libsqlite3.a -o test

insert: insert.c
	clang -g insert.c uuid.c libsqlite3.a -o insert

select: select.c product.c
	clang -g select.c product.c memory.c libsqlite3.a -o select

db.init:
	sqlite3 test.db < init.sql
