#include <stdio.h>
#include <stdbool.h>

#ifndef SMALL_DB_H
#define SMALL_DB_H

class smallDB {
    public:
        smallDB();
        smallDB(int hashSize);
        void debugDump();
        int getMaxRecSize();
        ~smallDB();
        
        void displayStatus(void);
        void setattr(int flags, int max, int nameSize, int defSize);
        
        int dbLoad(char *) ;
        
        int dbInsert(char *, char * ) ;
        bool findFirst(char *, char *) ;
        bool update(char *, void *);
        
    private:
        struct database *db;
};
#endif
