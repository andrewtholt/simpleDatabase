CXX=g++
CXX_FLAGS=-g -std=c++11

BINS=tstValue

all:	$(BINS)

value.o:	value.cpp value.h
	$(CXX) -c $(CXX_FLAGS) value.cpp -o value.o

tstValue:	tstValue.cpp value.o
	$(CXX) $(CXX_FLAGS) tstValue.cpp value.o -o  tstValue

clean:
	rm -f *.o cscope.out $(BINS)
