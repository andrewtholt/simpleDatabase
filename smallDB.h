#include <stdio.h>

#ifndef SMALL_DB_H
#define SMALL_DB_H

class smallDB {
    public:
        smallDB();
        ~smallDB();
        void displayStatus(void);
    private:
        struct database *db;
};
#endif
