#LookupBaker makefile
#(C) Arthur Sebastian Miller 2021

#object file directory
ODIR = build/object
#executable build directory
BDIR = build
#compiler configuration
CC = g++
FLAGS = -Wall --static -Ilib

default: LookupBaker

#main source
main.o: src/main.cpp
	$(CC) $(FLAGS) -o $(ODIR)/$@ -c src/main.cpp
#file dependencies
#toolkit.o: lib/animtools.cpp
#	$(CC) $(FLAGS) -o $(ODIR)/$@ -c lib/animtools.cpp
#colorspace.o: lib/colorspace.cpp
#	$(CC) $(FLAGS) -o $(ODIR)/$@ -c lib/colorspace.cpp

#build targets
LookupBaker: main.o
	$(CC) $(FLAGS) -o $(BDIR)/$@ $(ODIR)/main.o
	@echo "Build completed!"
clean:
	$(RM) $(ODIR)/*.o $(BDIR)/*~
	@echo "Build objects purged!"
run: LookupBaker
	@echo "Running the build!"
	./$(BDIR)/LookupBaker
