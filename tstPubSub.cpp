#include <iostream>

#include "pubsub.h"

using namespace std;

int main() {

    pubsub *ps = new pubsub();

    ps->display();

    ps->set("Test","Value");
    ps->display();

    ps->set("Test","Value");
    ps->display();
}
