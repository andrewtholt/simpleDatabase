#include <unistd.h>
#include <stdlib.h>
#include "db.h"
#include "smallDB.h"

int main() {
    int rc;
    smallDB *db;
    struct nlist *ptr;
    void *def;
    int maxSize=0;

    db = new smallDB();

    db->setattr(NEVER_SHRINK,0,10,10);
    
    db->dbLoad((char *)"tst.db");
    
    maxSize = db->getMaxRecSize();
    
    if( maxSize > 0 ) {
        def=malloc( maxSize );
    } else {
        fprintf(stderr,"Record size set to 0\n");
        exit(1);
    }
    db->displayStatus();
    
    ptr=db->findFirst((char *)"FRED",def);
    
    if( NULL== ptr) {
        printf("FRED Not found\n");
    }
    
    rc = db->dbInsert((char *)"FRED",(char *)"TEST");
    
    ptr=db->findFirst((char *)"FRED",def);
    if( NULL== ptr) {
        printf("FRED Not found\n");
    } else {
        printf("FRED found : %s\n",(char *)def);
    }
    
    printf("Test Done\n");

}
