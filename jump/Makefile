BIN := bin
SRC := src
TST := tst

all: clean compile test

clean:
	@echo "Cleaning..."
	@if test -d $(BIN); then rm -rf $(BIN)/*; else mkdir $(BIN); fi

compile:
	@echo "Compiling..."
	@gcc -Wall -o $(BIN)/jch_test $(TST)/jch_test.c

test:
	@echo "Testing..."
	@touch $(BIN)/results.txt
	@echo "START:  Testing  :START\n" >> $(BIN)/results.txt
	@echo "=======================\n" >> $(BIN)/results.txt
	$(BIN)/jch_test 10 10 >> $(BIN)/results.txt
	$(BIN)/jch_test 10 100 >> $(BIN)/results.txt
	$(BIN)/jch_test 10 1000 >> $(BIN)/results.txt
	$(BIN)/jch_test 100 10 >> $(BIN)/results.txt
	$(BIN)/jch_test 100 100 >> $(BIN)/results.txt
	$(BIN)/jch_test 100 1000 >> $(BIN)/results.txt
	$(BIN)/jch_test 1000 10 >> $(BIN)/results.txt
	$(BIN)/jch_test 1000 100 >> $(BIN)/results.txt
	$(BIN)/jch_test 1000 1000 >> $(BIN)/results.txt
	@echo "=======================\n" >> $(BIN)/results.txt
	@echo "FINISH: Testing :FINISH" >> $(BIN)/results.txt

results:
	@less $(BIN)/results.txt