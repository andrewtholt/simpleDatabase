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
#include <map>

#include "db.h"
#include "smallDB.h"

#define MAX_SUB (10)    // Maximum number of subscribers to a key
// 
// TODO Add a callback to run when a key value has changed
// 
// callBack(std::set subscribers, char *key, char *data);
//
// This knows how to contact the subscribers.
//
class pubsub {

    private:
        smallDB *db;
        char buffer[MAX_REC_SIZE];

        std::map<std::string, std::set<int> > fred;

        std::set<std::string> subscriber;
    public:
        pubsub();
        ~pubsub();

        std::tuple<bool, std::string>  get(const char *key);
        bool set(const char *key, const char *value);

        bool sub(const int id, const char *key);     // id is of the subscriber.
        bool unsub(const int id, const char *key);

        std::set<std::int> getSubscribers(const char *key);

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
