#ifndef _TESTING
#define _TESTING

#include <stdint.h>

#ifdef __cplusplus
#include <string>
#include <set>
#include <map>

#define PUB_ON_UPDATE (0)
#define PUB_ON_CHANGE (1)

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
        uint8_t getPubPolicy(std::string key);
        void    setPubPolicy(std::string key, uint8_t policy);

        std::set<void *>getSubscriber(std::string key);
        database();

        bool add(std::string key, std::string v);
        std::string get(std::string key);

        void sub(void *id, std::string key);
        void unsub(void *id, std::string key);

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
