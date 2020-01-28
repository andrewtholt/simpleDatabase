#ifndef _TESTING
#define _TESTING

#ifdef __cplusplus
#include <string>
#include "smallDB.h"

class pubsub {

    private:
        smallDB *db;
    public:
        pubsub();
        ~pubsub();

        char *get(char *key);
        bool *set(char *key, char *value);

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
