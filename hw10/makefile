all: clean compile run

clean:
	@echo "Cleaning compiled files...\n"
	@rm -rf test

compile:
	@echo "Compiling source code...\n"
	@gcc main.c -o test

run:
	@echo "Running tests..:\n"
	./test
	@echo "\nFinished running tests.\n"
