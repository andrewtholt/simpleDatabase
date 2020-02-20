#include "database.h"
#include <iostream>

using namespace std;

class myDatabase : public database {
    public:
        bool add(std::string, std::string) ;
}; 

bool myDatabase::add(std::string k, std::string v) {
    cout << "Here" << endl;
    bool f = database::add(k,v);

    return f;
}


int main() {
    uint8_t tst=1;

    myDatabase db;

    bool updated;

    updated = db.add("TEST","DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    updated = db.add("TEST","DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    updated = db.add("TEST","DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    updated = db.add("TEST","MORE DATA");

    cout << unsigned(tst++) << "  " << updated << endl;
}

