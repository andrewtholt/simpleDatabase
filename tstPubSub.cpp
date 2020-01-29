#include <iostream>

#include "pubsub.h"

using namespace std;

int main() {

    bool c=false;

    pubsub *ps = new pubsub();

    ps->display();

    c=ps->set((char *)"Test", (char *)"Value");
    ps->display();

    c=ps->set((char *)"Test",(char *)"Value");
    ps->display();
}
