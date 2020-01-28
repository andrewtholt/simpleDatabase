#
ARCHIVE=$(HOME)/Archive
NAME=simpleDatabase
ARCHIVE_FILE=$(ARCHIVE)/$NAME).tar

BINS=tst tstSmallDB tstPubSub

CC = cc -g
GPP = g++ -g

FLAG=BackUp.txt

all:	$(BINS)

tst:	tst.o db.o
	$(CC) tst.o db.o -o tst

tstPubSub:	tstPubSub.cpp smallDB.o db.o pubsub.o
	$(GPP) tstPubSub.cpp db.o smallDB.o pubsub.o -o tstPubSub

pubsub.o:	smallDB.o pubsub.h
	$(GPP) -c pubsub.cpp -o pubsub.o

db.o:	db.c db.h
	$(CC) -c $(CFLAGS) db.c -o db.o

tst.o:	tst.c db.h
	$(CC) -c $(CFLAGS) tst.c -o tst.o

smallDB.o:	smallDB.cpp smallDB.h
	$(GPP) -c smallDB.cpp -o smallDB.o

tstSmallDB:	tstSmallDB.cpp smallDB.o db.o
	$(GPP) tstSmallDB.cpp smallDB.o db.o -o tstSmallDB

clean:
	rm -f $(BINS) tst core *.o *~ cscope.out

backup:
	rm -f tst core *.o *~ cscope.out
	( cd .. ; tar cvf $(ARCHIVE_FILE) ./$(NAME) )
	touch BackUp.txt
