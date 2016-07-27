#include <stdio.h>

#ifndef SMALL_DB_H
#define SMALL_DB_H

class smallDB {
    public:
        smallDB();
        ~smallDB();
        void displayStatus(void);
        void setattr(int flags, int max, int nameSize, int defSize);
        int dbLoad(char *) ;
    private:
        struct database *db;
};
#endif
