BIN := bin

all:
	clean
	hash_test

clean:
	@if test -d $(BIN); then rm -rf $(BIN)/*; else mkdir $(BIN); fi

hash_test:
	@gcc -Wall hash_test.c -o bin/ht.o
