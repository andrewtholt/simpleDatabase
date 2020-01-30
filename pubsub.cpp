/***********************************************************************
 * AUTHOR:  <andrewh>
 *   FILE: .//pubsub.cpp
 *   DATE: Tue Jan 28 08:56:34 2020
 *  DESCR: 
 ***********************************************************************/
#include "pubsub.h"

/***********************************************************************
 *  Method: pubsub::pubsub
 *  Params: 
 * Effects: 
 ***********************************************************************/
pubsub::pubsub() {
    db = new smallDB();
}


/***********************************************************************
 *  Method: pubsub::~pubsub
 *  Params: 
 * Effects: 
 ***********************************************************************/
pubsub::~pubsub()
{
}


/***********************************************************************
 *  Method: pubsub::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void pubsub::display() {
    db->displayStatus();
}


/***********************************************************************
 *  Method: pubsub::get
 *  Params: char *key
 * Returns: char *
 * Effects: 
 ***********************************************************************/
std::tuple<bool, std::string> pubsub::get(const char *key) {

    char def[MAX_REC_SIZE];
    bzero(def,MAX_REC_SIZE);

//    std::string res;

    bool found=db->findFirst(key, (char *)def);

    if( found ) {
        printf("get %s\n",def);
    } // else {
//        res = "";
//    }

    return std::make_tuple(found, std::string(def ));
}

/***********************************************************************
 *  Method: pubsub::set
 *  Params: char *key, char *value
 * Returns: bool *
 * Effects: 
 ***********************************************************************/
bool pubsub::set(const char *key, const char *value) {
    bool changed=false;

    bool found = db->findFirst(key, NULL);
    if (found) {
        changed = db->update((char *)key,(char *)value);
    } else {
        changed = db->dbInsert((char *)key,(char *)value);
        changed=true;
    }
    return changed;
}


/***********************************************************************
 *  Method: pubsub::sub
 *  Params: int id, char *key
 * Returns: bool
 * Effects: 
 ***********************************************************************/
bool pubsub::sub(int id, const char *key) {
    bool fail=true;

    return fail;
}


/***********************************************************************
 *  Method: pubsub::unsub
 *  Params: int id, char *key
 * Returns: bool
 * Effects: 
 ***********************************************************************/
bool pubsub::unsub(const int id, const char *key) {
    bool failed=true;

    return failed;
}


