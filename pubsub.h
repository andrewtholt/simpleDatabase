#ifndef _TESTING
#define _TESTING

// #define MAX_DEF (64)

#include <strings.h>
#include <string.h>

#ifdef __cplusplus
#include <string>
#include <tuple>
#include <iostream>
#include <set>

#include "db.h"
#include "smallDB.h"

class pubsub {

    private:
        smallDB *db;
        char buffer[MAX_REC_SIZE];

        std::set<std::string> subscriber;
    public:
        pubsub();
        ~pubsub();

        std::tuple<bool, std::string>  get(const char *key);
        bool set(const char *key, const char *value);

        bool sub(const int id, const char *key);
        bool unsub(const int id, const char *key);

//        std::array<std::string> getSubscribers(const char *key);

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
