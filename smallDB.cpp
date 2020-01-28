#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "smallDB.h"


extern "C" {
#include "db.h"
   struct database *db_create(int ) ;
//   void db_status( struct database *);
   void db_setattr(struct database *, int, int , int , int );
   
    bool db_update(struct nlist *, char *, struct database *) ;
    int db_load(char *, struct database *);
    int db_load(char *fname, struct database *db);
//    struct nlist *find_first(char *, struct database *) ;
//    struct nlist *db_install(char *,char *, struct database *);
}

smallDB::smallDB(int hash) {
    printf("Created hash=%d\n", hash);

    db = db_create(hash);
    if( NULL == db ) {
        fprintf(stderr, "DB Create failed.\n");
    }
}

smallDB::smallDB() {
    printf("Created\n");

    db = db_create(101);
    if( NULL == db ) {
        fprintf(stderr, "DB Create failed.\n");
    }
}

void smallDB::debugDump() {
// void debug_dump(struct database *db) {
    debug_dump(db) ;
}

bool smallDB::update(char *key, void *def) {
//    bool fail=true;
    bool changed=false;

    struct nlist *res;
    
    res = find_first(key,db);
    
    /*
    if(!res) { // key does not exist
        fail=true;
    } else {  // Key does exist
        changed=db_update(res,(char *)def,db);
        fail=false;
    }
    */
    
    if(res != NULL) { // key does not exist
        changed=db_update(res,(char *)def,db);
    }
    
    return changed;
}

int smallDB::getMaxRecSize() {
    return MAX_REC_SIZE;
}


void smallDB::setattr(int flags, int max, int nameSize, int defSize) {
    db_setattr(db,flags,max,nameSize,defSize);
}

void smallDB::displayStatus(void) {
    db_status(db);
}

int smallDB::dbLoad(char *fname) {
    int rc=0;
    
    rc = db_load(fname, db);
    
    return rc;
} 

int smallDB::dbInsert(char *key, char *def ) {
    
    int rc=0;
    struct nlist *ptr;
    
    ptr =  db_install(key,def, db);
    
    if(!ptr) {
        rc=0;
    } else {
        rc=1;
    }
    
    return rc;
}
// 
// TODO Don't like that this returns pointer to structure, should return void* to def.
// 
// struct nlist *smallDB::findFirst(char *key, void *def) {
bool smallDB::findFirst(char *key, void *def) {
    struct nlist *res;
//    struct nlist *find_first(char *key, struct database *db)
    res = find_first(key,db);
    
    if(!res) {
        def=NULL;
    } else {
        memcpy(def, res->def, MAX_REC_SIZE);
        def = res->def;
    }   
    
    return res;
}



smallDB::~smallDB() {
    printf("Destroyed\n");
}

