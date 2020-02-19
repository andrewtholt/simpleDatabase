/***********************************************************************
 * AUTHOR:  <andrewh>
 *   FILE: .//value.cpp
 *   DATE: Wed Feb 19 13:06:53 2020
 *  DESCR: 
 ***********************************************************************/
#include "value.h"
#include <iostream>


// void defaultCallback(uint8_t id, std::string key, std::string val) {
void defaultCallback(value *ptr) {
    ptr->display();
    std::cout << "Default callback, change me," << std::endl;
}
/***********************************************************************
 *  Method: value::value
 *  Params: 
 * Effects: 
 ***********************************************************************/
value::value() {
    commonInit();
}


/***********************************************************************
 *  Method: value::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void value::display() {
    std::cout << "=========================" << std::endl;
    std::cout << "Value    :" << v << std::endl;
    std::cout << "On Change:" << onChange << std::endl;
    std::cout << "Subscribers" << std::endl;
    for(auto id : subscriber) {
        std::cout << "\t" << unsigned(id) << std::endl;
    }
}


/***********************************************************************
 *  Method: value::value
 *  Params: std::string
 * Effects: 
 ***********************************************************************/
value::value(std::string val) {
    commonInit();
    v = val;
}


/***********************************************************************
 *  Method: value::commonInit
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void value::commonInit() {
    onChange = true;
    callback=defaultCallback;
}


/***********************************************************************
 *  Method: value::addSubscriber
 *  Params: uint8_t
 * Returns: void
 * Effects: 
 ***********************************************************************/
void value::addSubscriber(uint8_t id) {
    subscriber.insert(id);
}


/***********************************************************************
 *  Method: value::set
 *  Params: std::string
 * Returns: void
 * Effects: 
 ***********************************************************************/
void value::set(std::string in) {

    bool changed=false;

    changed = (v != in) ? true : false ;

    v = in;
    
    if( subscriber.size() > 0) {
        if(changed && onChange) {
            std::cout << "Changed" << std::endl;
            (*callback)(this);
        }
    } else {
        std::cout << "No subscribers." << std::endl;
    }
}


/***********************************************************************
 *  Method: value::get
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string value::get() {
    return v;
}


/***********************************************************************
 *  Method: value::setOnChange
 *  Params: bool
 * Returns: void
 * Effects: 
 ***********************************************************************/
void value::setOnChange(bool f) {
    onChange = f;
}


