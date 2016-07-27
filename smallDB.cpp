#include <stdio.h>
#include "smallDB.h"

extern "C" {
   struct database *db_create(int ) ;
   void db_status( struct database *);
   void db_setattr(struct database *, int, int , int , int );

}

smallDB::smallDB() {
    printf("Created\n");

    db = db_create(101);
    if( NULL == db ) {
        fprintf(stderr, "DB Create failed.\n");
    }
}

void smallDB::setattr(int flags, int max, int nameSize, int defSize) {
    // void db_setattr(struct database *db, int flags, int max, int nameSize, int defSize)
    db_setattr(db,flags,max,nameSize,defSize);
}

void smallDB::displayStatus(void) {
    db_status(db);
}


smallDB::~smallDB() {
    printf("Destroyed\n");
}

