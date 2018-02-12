all: tree_map_test.c
	@echo "Compiling tests..."
	@rm -rf bin
	@mkdir bin
	@gcc -Wall tree_map_test.c ../src/bin/table.o ../src/bin/tree_map.o -o bin/tree_map_test.o -lssl -lcrypto
	@echo "Running tests..."
	@bin/tree_map_test.o
	
