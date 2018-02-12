all: tree_map_test.o
	@echo "Running tests...\n"
	@bin/tree_map_test.o

tree_map_test.o:
	@echo "Compiling tests..."
	@gcc -Wall tree_map_test.c ../src/bin/table.o ../src/bin/tree_map.o -o bin/tree_map_test.o -lssl -lcrypto
