/***********************************************************************
 * AUTHOR:  <andrewh>
 *   FILE: .//database.cpp
 *   DATE: Thu Feb 20 08:08:20 2020
 *  DESCR: 
 ***********************************************************************/
#include "database.h"
#include <string.h>
#include <iostream>

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
void
database::display()
{
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

    if(found == 0) {
        std::cout << key <<" not found" << std::endl;

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

    return changed;
    
}


