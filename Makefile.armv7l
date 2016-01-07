#
ARCHIVE=$(HOME)/Archive
ARCHIVE_FILE=$(ARCHIVE)/smallDatabase.tar

CC = cc -g

FLAG=BackUp.txt

tst:	tst.o db.o
	$(CC) tst.o db.o -o tst

db.o:	db.c db.h
	$(CC) -c $(CFLAGS) db.c -o db.o

tst.o:	tst.c db.h
	$(CC) -c $(CFLAGS) tst.c -o tst.o

clean:
	rm -f tst core *.o *~ cscope.out

backup:
	rm -f tst core *.o *~ cscope.out
	( cd .. ; tar cvf $(ARCHIVE_FILE) ./smallDatabase )
	touch BackUp.txt
