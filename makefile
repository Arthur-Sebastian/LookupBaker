#Function baker makefile
#(C) Arthur Sebastian Miller 2021

CC = g++
FLAGS = -Wall --static

default: baker

#source files, tools
main.o: main.cpp
	$(CC) $(FLAGS) -o build/main.o -c main.cpp
toolkit.o: lib/animtools.cpp
	$(CC) $(FLAGS) -o build/toolkit.o -c lib/animtools.cpp
colorspace.o: lib/colorspace.cpp
	$(CC) $(FLAGS) -o build/colorspace.o -c lib/colorspace.cpp
	
#build targets
baker: main.o toolkit.o colorspace.o
	$(CC) $(FLAGS) -o build/LookupBaker build/main.o build/toolkit.o build/colorspace.o
	@echo "Build completed!"
clean:
	$(RM) build/*.o build/*~
	clear
	@echo "Build directory purged!"
run: baker
	clear
	@echo "Running the build!"
	./build/LookupBaker
