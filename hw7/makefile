all: clean compile run

clean:
	@echo "*** Cleaning compiled files ***\n"
	@echo rm -f main

compile: main.c wordlist.txt
	@echo "*** Compiling the source file ***\n"
	@echo gcc main.c -o test

run:
	@echo "*** Running tests ***\n"
	./test
	@echo "*********************\n*** Finished running tests ***\n*********************\n"

