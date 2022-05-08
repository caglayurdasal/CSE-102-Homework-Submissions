all: clean compile run

clean:
	@echo "Cleaning compiled files...\n"
	@rm -f test

compile: main.c util.c util.h
	@echo "Compiling...\n"
	@gcc main.c util.c -o test

run:
	@echo "Running tests...\n"
	./test
	@echo "\n*************************\nFinished running tests.\n"