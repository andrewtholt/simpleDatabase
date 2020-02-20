#ifndef _TESTING
#define _TESTING

#include <stdint.h>

#ifdef __cplusplus
#include <string>
#include <set>
#include <map>

#define PUB_ON_UPDATE (0)
#define PUB_ON_CHANGE (0)

struct dbValue {
    std::string value;

    uint8_t pubPolicy;

    std::set<void *> subscriber;
};

class database {
    private:
        std::map<std::string, struct dbValue *> data;
        void commonInit();
    public:

        database();
        bool add(std::string key, std::string v);
        std::string databaseing;

        void display();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

struct database* newClass();
void display(struct database*);

#ifdef __cplusplus
}
#endif

#endif // _TESTING
