all: clean compile run

clean:
	@echo "Removing compiled files...\n****************************\n"
	@rm -f *.o
	@rm -f test
	@rm -f temp.txt

compile:
	@echo "Compiling...\n****************************\n"
	@gcc main.c -o test -lm

run:
	@echo "Running tests...\n****************************\n"
	./test
	
	@echo "Finished running tests.\n****************************\n"
