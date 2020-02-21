/***********************************************************************
 * AUTHOR:  <andrewh>
 *   FILE: .//database.cpp
 *   DATE: Thu Feb 20 08:08:20 2020
 *  DESCR: 
 ***********************************************************************/
#include "database.h"
#include <string.h>
#include <iostream>
#include <set>

/***********************************************************************
 *  Method: database::database
 *  Params: 
 * Effects: 
 ***********************************************************************/
database::database() {
    commonInit();
}


/***********************************************************************
 *  Method: database::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void database::display() {

    /*
    std::cout << "===============================" << std::endl;
    for(std::pair<std::string, struct dbValue* > element : data ) {
        std::cout << "Key         : " << element.first << std::endl;
        std::cout << "Value       : " << (element.second)->value << std::endl;
        std::cout << "Pub Policy  : " << unsigned( (element.second)->pubPolicy) << std::endl;
        std::cout << "Sub Count   : " << unsigned( (element.second)->subscriber.size()) << std::endl;
    }
    */
}


/***********************************************************************
 *  Method: database::commonInit
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void database::commonInit() {
    std::cout << "Common Init" << std::endl;

}


/***********************************************************************
 *  Method: database::add
 *  Params: std::string key, std::string v
 * Returns: bool
 * Effects: 
 ***********************************************************************/
bool database::add(std::string key, std::string v) {

    bool changed = false;
    int found=data.count( key );

    /*
    if(found == 0) {
        std::cout << key <<" not found" << std::endl;

        data[key] = new dbValue(v);

        struct dbValue *tmp  = (struct dbValue *)malloc(sizeof(struct dbValue));
        memset(tmp,0,sizeof(struct dbValue));

        tmp->value = v ;

        data[ key ] = tmp;
    } else  {
        std::cout << key <<" found" << std::endl;

        if  ( data[key]->value == v) {
            changed = false;
        } else {
            data[key]->value = v;
            changed = true;
        }
    }
    */

    return changed;
    
}


/***********************************************************************
 *  Method: database::getPubPolicy
 *  Params: std::string key
 * Returns: uint8_t
 * Effects: 
 ***********************************************************************/
uint8_t database::getPubPolicy(std::string key) {
    uint8_t p=PUB_ON_UPDATE;

    int found=data.count( key );

    if(found == 1) {
//        p = data[ key ]->pubPolicy;
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

    int found=data.count( key );

    if(found == 1) {
//        data[ key ]->pubPolicy = policy;
    }

}


/***********************************************************************
 *  Method: database::get
 *  Params: std::string key
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string database::get(std::string key) {
    std::string d = "";
    /*
    int found=data.count( key );

    if(found == 1) {
        d = data[key]->value;

        std::set<void *>a = data[key]->subscriber;

        std::cout << a.size() << std::endl;
    } else {
        d="<NO DATA>";
    }
    */
    return d;
}


/***********************************************************************
 *  Method: database::sub
 *  Params: void *id, std::string key
 * Returns: void
 * Effects: 
 ***********************************************************************/
void database::sub(void *id, std::string key) {
    int found=data.count( key );

    if(found == 1) {
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
 *  Method: database::getSubscriber
 *  Params: std::string key
 * Returns: std::set<void *>
 * Effects: 
 ***********************************************************************/
std::set<void *>database::getSubscriber(std::string key) {
    return data[key]->subscriber;
}


