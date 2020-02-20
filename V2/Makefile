CXX=g++
CXX_FLAGS=-g -std=c++11

BINS=tstValue tstDb

all:	$(BINS)

db.o:	db.cpp db.h value.o
	$(CXX) -c $(CXX_FLAGS) db.cpp -o db.o

value.o:	value.cpp value.h
	$(CXX) -c $(CXX_FLAGS) value.cpp -o value.o

tstValue:	tstValue.cpp value.o
	$(CXX) $(CXX_FLAGS) tstValue.cpp value.o -o  tstValue

tstDb:	tstDb.cpp db.o
	$(CXX) $(CXX_FLAGS) tstDb.cpp db.o value.o -o  tstDb

clean:
	rm -f *.o cscope.out $(BINS)
