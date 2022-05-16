all: clean compile run

clean: 
	@echo "Cleaning compiled files...\n"
	@rm -rf test

compile:
	@echo "Compiling main.c...\n"
	@gcc main.c -o test

run: main.c
	@echo "Running tests...\n"
	./test
	@echo "\n*******************************\n"
	@echo "*** Finished running tests  ***\n"
	@echo "*******************************\n"

