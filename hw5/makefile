all: clear clean compile run

clear:
	@clear

clean:
	@echo "Cleaning compiled files...\n"
	@rm -f main

compile:
	@echo "Compiling...\n"
	@gcc  main.c -o main -lm

run:
	@echo "Running the program..:\n"
	./main
	@echo "Finished running the program.\n\n"