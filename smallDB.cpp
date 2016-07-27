#include <stdio.h>
#include "smallDB.h"

extern "C" {
   struct database *db_create(int ) ;
   void db_status( struct database *);
}

smallDB::smallDB() {
    printf("Created\n");

    db = db_create(101);
    if( NULL == db ) {
        fprintf(stderr, "DB Create failed.\n");
    }
}

void smallDB::displayStatus(void) {
    db_status(db);
}


smallDB::~smallDB() {
    printf("Destroyed\n");
}

