#include <iostream>

#include "pubsub.h"

using namespace std;

int main() {

    bool c=false;

    pubsub *ps = new pubsub();

    ps->display();

    c=ps->set((char *)"Test", (char *)"Value");
    // 
    // If c is true the definition changed.
    // We can decide here if we want to do anything about it.
    //
    ps->display();

    c=ps->set((char *)"Test",(char *)"Value");
    ps->display();

    bool changed;
    string def;

    tie(changed, def) = ps->get((char *)"Test");

    cout << "Found    : " << changed << endl;
    cout << "Value    : " << def << endl;

    tie(changed, def) = ps->get((char *)"Bill");

    cout << "Found    : " << changed << endl;
    cout << "Value    : " << def << endl;
}
