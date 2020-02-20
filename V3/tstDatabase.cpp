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
    bool pub = false;

    // Changed
    uint8_t p = getPubPolicy(k);

    switch(p) {
        case PUB_ON_UPDATE:
            if(f == false ) {
                cout << k << " updated, so publish" << endl;
                pub = true;
            } else {
                pub = false;
            }
            break;
        case PUB_ON_CHANGE:
            if(f == true ) {
                cout << k << " changed, so publish" << endl;
                pub = true;
            } else {
                pub = false;
            }

            break;
    }

    return pub;
}

int main() {
    uint8_t tst=1;

    myDatabase db;

    bool updated;

    cout << "Make policy publish on update" << endl;
    db.setPubPolicy("TEST", PUB_ON_UPDATE);

    updated = db.add("TEST","DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    updated = db.add("TEST","DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    cout << "Make policy publish on change" << endl;
    db.setPubPolicy("TEST", PUB_ON_CHANGE);
    updated = db.add("TEST","DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    updated = db.add("TEST","MORE DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    updated = db.add("TEST","MORE DATA");

    cout << unsigned(tst++) << "  " << updated << endl;
}

