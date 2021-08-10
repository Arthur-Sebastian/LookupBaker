#Function baker makefile
#(C) Arthur Sebastian Miller 2021

CC = g++
FLAGS = -Wall --static

default: baker

#source files, tools
toolkit.o: lib/animtools.cpp
	$(CC) $(FLAGS) -o build/toolkit.o -c lib/animtools.cpp
main.o: main.cpp
	$(CC) $(FLAGS) -o build/main.o -c main.cpp
	
#build targets
baker: toolkit.o main.o
	$(CC) $(FLAGS) -o build/LookupBaker build/main.o build/toolkit.o
	@echo "Build completed!"
clean:
	$(RM) build/*.o build/*~
	clear
	@echo "Build directory purged!"
run: baker
	clear
	@echo "Running the build!"
	./LookupBaker
