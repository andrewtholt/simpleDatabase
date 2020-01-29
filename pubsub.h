#ifndef _TESTING
#define _TESTING

#define MAX_DEF (64)

#include <strings.h>
#ifdef __cplusplus
#include <string>
#include <iostream>
#include "smallDB.h"

class pubsub {

    private:
        smallDB *db;
        char buffer[MAX_DEF];
    public:
        pubsub();
        ~pubsub();

        char *get(char *key);
        void set(char *key, char *value);

        bool sub(int id, char *key);
        bool unsub(int id, char *key);

        void display();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

struct pubsub *newClass();
void display(struct pubsub*);

#ifdef __cplusplus
}
#endif

#endif // _TESTING
