#include "db.h"
#include "smallDB.h"

int main() {
    smallDB *db;

    db = new smallDB();

    db->displayStatus();

}
