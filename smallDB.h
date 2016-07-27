#include <stdio.h>

#ifndef SMALL_DB_H
#define SMALL_DB_H

class smallDB {
    public:
        smallDB();
        int getMaxRecSize();
        ~smallDB();
        void displayStatus(void);
        void setattr(int flags, int max, int nameSize, int defSize);
        int dbLoad(char *) ;
        int dbInsert(char *, char * ) ;
        struct nlist *findFirst(char *, void *) ;
    private:
        struct database *db;
};
#endif
