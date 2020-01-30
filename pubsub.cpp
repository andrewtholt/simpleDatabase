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
std::tuple<bool, std::string> pubsub::get(char *key) {

    char def[MAX_DEF];
    bzero(def,MAX_DEF);

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
bool pubsub::set(char *key, char *value) {

//    bzero(buffer,MAX_DEF);
    bool rc=false;

    bool found = db->findFirst(key, NULL);
    if (found) {
        rc = db->update((char *)key,(char *)value);
    } else {
        rc = db->dbInsert((char *)key,(char *)value);
    }
    return rc;
}


/***********************************************************************
 *  Method: pubsub::sub
 *  Params: int id, char *key
 * Returns: bool
 * Effects: 
 ***********************************************************************/
bool
pubsub::sub(int id, char *key)
{
}


/***********************************************************************
 *  Method: pubsub::unsub
 *  Params: int id, char *key
 * Returns: bool
 * Effects: 
 ***********************************************************************/
bool
pubsub::unsub(int id, char *key)
{
}


