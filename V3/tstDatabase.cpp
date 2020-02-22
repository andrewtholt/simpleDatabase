#include "database.h"
#include <iostream>

using namespace std;

class myDatabase : public database {
    private:
        void doPublish(std::string key);
    public:
        bool add(std::string, std::string) ;
        void act( const void *id, const std::string key, std::string value) ;
}; 

void myDatabase::act( const void *id, const std::string key, std::string value) {
        printf("PUBLISH ID  : %04x\n", id);
        printf("       KEY  : %04x\n", key);
        printf("       VALUE: %04x\n", key);
}

void myDatabase::doPublish(std::string key) {

    const std::set<void *> *ptr = getSubscriber(key); 
    const std::string value = get(key);

//    std::set<void *> ptr = getSubscriber( key) ;

    if( ptr->size() > 0 ) {
        for( auto id : *ptr ) {
            act( id, key, value) ;
        }
    }
}

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

    if( pub ) {
        doPublish(k);
    }

    return pub;
}

int main() {
    uint8_t tst=1;

    myDatabase db;

    bool updated;

    updated = db.add("TEST","DATA");
    cout << unsigned(tst++) << "  " << updated << endl;

    cout << db.get("TEST") << endl;


//    cout << "Make policy publish on update" << endl;
//    db.setPubPolicy("TEST", PUB_ON_UPDATE);

    updated = db.add("TEST","NEW_DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    cout << "Make policy publish on change" << endl;
    db.setPubPolicy("TEST", PUB_ON_CHANGE);
    updated = db.add("TEST","DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    db.sub( (void *)1, "TEST" );
    updated = db.add("TEST","MORE DATA");
    db.display();
    exit(0);

    updated = db.add("TEST","MORE DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    updated = db.add("TEST","MORE DATA");

    cout << unsigned(tst++) << "  " << updated << endl;

    cout << db.get("TEST") << endl;
    cout << db.get("A TEST") << endl;

    db.display();

    db.sub( (void *)1, "TEST" );
    cout << db.get("TEST") << endl;

    db.display();


}

