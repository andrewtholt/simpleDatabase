#include "smallDB.h"

extern "C" {
   struct database *db_create(int ) ;
}

smallDB::smallDB() {
    struct database *db;
    printf("Created\n");

    db = db_create(101);
}

smallDB::~smallDB() {
    printf("Destroyed\n");
}

