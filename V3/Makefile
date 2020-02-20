CXX=g++
CXX_FLAGS=-g -std=c++11

BINS=tstDatabase

all:	$(BINS)

tstDatabase:	tstDatabase.cpp database.o
	$(CXX) $(CXX_FLAGS) tstDatabase.cpp database.o -o tstDatabase

database.o:	database.cpp database.h 
	$(CXX) -c $(CXX_FLAGS) database.cpp -o database.o

clean:
	rm -f *.o cscope.out $(BINS)
