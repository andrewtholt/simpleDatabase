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
char *
pubsub::get(char *key)
{
}


/***********************************************************************
 *  Method: pubsub::set
 *  Params: char *key, char *value
 * Returns: bool *
 * Effects: 
 ***********************************************************************/
void pubsub::set(char *key, char *value) {

//    bzero(buffer,MAX_DEF);
    int rc=0;

    bool found = db->findFirst(key, NULL);
    if (found) {
        rc = db->update((char *)key,(char *)value);
    } else {
        rc = db->dbInsert((char *)key,(char *)value);
    }
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


