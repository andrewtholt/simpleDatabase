
CFLAGS=-fprofile-arcs -ftest-coverage

tester.o:	tester.c
	gcc $(CFLAGS) -c tester.c -o tester.o

tester:	tester.o 
	gcc $(CFLAGS) tester.o -o tester -lcunit -L. -lsdb 

test:	tester
	splint fred.c && ./tester && gcov fred.c

# clean:
#	rm -f *.o tester *.gc??
