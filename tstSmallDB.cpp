#include "db.h"
#include "smallDB.h"

int main() {
    smallDB *db;

    db = new smallDB();


    db->setattr(NEVER_SHRINK,0,10,10);
    
    db->dbLoad((char *)"tst.db");
    db->displayStatus();

}
