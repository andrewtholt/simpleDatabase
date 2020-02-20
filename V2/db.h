#ifndef _TESTING
#define _TESTING

#ifdef __cplusplus

#include <string>

#include <map>
#include "value.h"

class db {
    private:

//        std::map<std::string, value *> fred;

        value *fred;
    public:
        db();

        void add(std::string key, std::string value);

        void display();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

struct db* newClass();
void display(struct db*);

#ifdef __cplusplus
}
#endif

#endif // _TESTING
