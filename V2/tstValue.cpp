#include "value.h"
#include <iostream>

using namespace std;

void myCallback(value *ptr) {
    cout << "Local callback" << endl;

    ptr->display();
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
