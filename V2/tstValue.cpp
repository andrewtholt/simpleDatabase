#include "value.h"
#include <iostream>

int main() {
    value *tst = new value("TST");

    tst->display();

    tst->set("NEWER_TST");

    tst->addSubscriber(2);

    tst->display();

    tst->set("NEW_TST");

    tst->display();

    tst->setOnChange(false);

    tst->display();
}
