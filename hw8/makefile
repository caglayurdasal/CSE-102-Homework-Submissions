all: clean compile run

clean:
	@echo "Cleaning compiled files...\n"
	@rm -rf *.o

compile: main.c util.c util.h
	@echo "Compiling...\n"
	@gcc main.c -o test

run:
	@echo "Running tests...\n"
	./test
	@echo "Finished running tests.\n"