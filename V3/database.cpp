/***********************************************************************
 * AUTHOR:  <andrewh>
 *   FILE: .//database.cpp
 *   DATE: Fri Feb 21 12:41:37 2020
 *  DESCR: 
 ***********************************************************************/
#include "database.h"

/***********************************************************************
 *  Method: database::commonInit
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void
database::commonInit()
{
}


/***********************************************************************
 *  Method: database::getPubPolicy
 *  Params: std::string key
 * Returns: uint8_t
 * Effects: 
 ***********************************************************************/
uint8_t database::getPubPolicy(std::string key) {

    uint8_t p = PUB_ON_UPDATE;

    if( data.count( key ) == 1 ) {
        p = data[key]->getPubPolicy( );
    }
    return p;
}


/***********************************************************************
 *  Method: database::setPubPolicy
 *  Params: std::string key, uint8_t policy
 * Returns: void
 * Effects: 
 ***********************************************************************/
void database::setPubPolicy(std::string key, uint8_t policy) {
    if( data.count( key ) == 1 ) {
        data[key]->setPubPolicy( policy );
    }
}


/***********************************************************************
 *  Method: database::getSubscriber
 *  Params: std::string key
 * Returns: std::set<void *>
 * Effects: 
 ***********************************************************************/
std::set<void *> *database::getSubscriber(std::string key) {
    std::set<void *> *s = NULL;

    if( data.count( key ) == 1 ) {
       s = data[key]->getSubscriber();
    }
    return s;
}


/***********************************************************************
 *  Method: database::database
 *  Params: 
 * Effects: 
 ***********************************************************************/
database::database()
{
}


/***********************************************************************
 *  Method: database::add
 *  Params: std::string key, std::string v
 * Returns: bool
 * Effects: 
 ***********************************************************************/
bool database::add(std::string key, std::string v) {

    bool flag=false;

    if( data.count( key ) == 0 ) {
        data[key] = new dbValue( v );
        flag=true;
    } else {
        if( v == data[key]->getValue() ) {
            flag = false;
        } else {
            data[key]->setValue( v ) ;
            flag=true;
        }
    }
    return flag;
}


/***********************************************************************
 *  Method: database::get
 *  Params: std::string key
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string database::get(std::string key) {
    std::string result="<NO DATA>";

    if( data.count( key ) == 1 ) {
        result = data[key]->getValue();
    }

    return result;

}


/***********************************************************************
 *  Method: database::sub
 *  Params: void *id, std::string key
 * Returns: void
 * Effects: 
 ***********************************************************************/
void database::sub(void *id, std::string key) {

    if( data.count( key ) == 1 ) {
        data[key]->addSubscriber( id );
    }
}


/***********************************************************************
 *  Method: database::unsub
 *  Params: void *id, std::string key
 * Returns: void
 * Effects: 
 ***********************************************************************/
void
database::unsub(void *id, std::string key)
{
}


/***********************************************************************
 *  Method: database::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void database::display() {

    for(std::pair<std::string, dbValue* > element : data ) {
        std::cout << "Key   : " << element.first << std::endl;
        data[element.first]->display();
    }

}


