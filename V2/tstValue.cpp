#include "value.h"
#include <iostream>

using namespace std;

void myCallback(uint8_t id, std::string val) {
// void myCallback(value *ptr) {
    cout << "Local callback" << endl;
    cout << "\t" << unsigned(id) << endl;
    cout << "\t" << val << endl;
    //
    // TODO Add comms mechanism to notify subscriber
    //
}

int main() {
    value *tst = new value("TST");

    tst->display();

    tst->set("NEWER_TST");

    tst->addSubscriber(2);

    tst->display();

    tst->setCallback( myCallback );

    tst->set("NEW_TST");

    tst->display();

    tst->setOnChange(false);

    tst->display();
}
