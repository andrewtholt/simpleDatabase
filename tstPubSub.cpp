#include <iostream>

#include "pubsub.h"

using namespace std;

int main() {

    pubsub *ps = new pubsub();

    ps->display();

    ps->set((char *)"Test", (char *)"Value");
    ps->display();

    ps->set((char *)"Test",(char *)"Value");
    ps->display();
}
