#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "db.h"
#include "smallDB.h"

int main() {
    int rc;
    smallDB *db;
    struct nlist *ptr;
    void *def;
    int maxSize=0;
    bool found=false;

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
    
    found=db->findFirst((char *)"FRED",def);
    
    if( !found) {
        printf("FRED Not found\n");
    }
    
    rc = db->dbInsert((char *)"FRED",(char *)"TEST");

    bool changed=false;

    changed = db->update((char *)"FRED",(void *)"OLD");
    (changed) ? printf("Updated\n") : printf("No change\n") ;

    changed = db->update((char *)"FRED",(void *)"NEW");
    (changed) ? printf("Updated\n") : printf("No change\n") ;

    changed = db->update((char *)"FRED",(void *)"NEW");
    (changed) ? printf("Updated\n") : printf("No change\n") ;

    changed = db->update((char *)"FRED",(void *)"NEW");
    (changed) ? printf("Updated\n") : printf("No change\n") ;

    
    found=db->findFirst((char *)"FRED",def);
    if( found) {
        printf("FRED found : %s\n",(char *)def);
    } else {
        printf("FRED Not found\n");
    }
    
//    db->debugDump();
    printf("Test Done\n");

}
