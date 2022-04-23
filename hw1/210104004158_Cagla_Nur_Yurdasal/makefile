all: clean compile run

clean:
	@echo "Removing compiled files and text file.\n*********************************"
	@rm -f *.o
	@rm -f main
	@rm -rf *.txt

compile: main.c utils.c utils.h
	@echo "Compiling.\n*********************************"
	@gcc -c main.c
	@gcc -o main main.c utils.c

run:
	@echo "Running the program.\n*********************************"
	@./main
	@echo "*********************************\nCompleted.\n"