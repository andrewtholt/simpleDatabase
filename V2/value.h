#ifndef _TESTING
#define _TESTING

#include <stdint.h>
#ifdef __cplusplus
#include <string>
#include <set>


#include <string>
class value {

    private:
        std::string v;

        std::set<uint8_t> subscriber;

        bool onChange;  // When true only notify subscribers if a change took place.

        void commonInit();
        void (*callback)(uint8_t, std::string );
//        void (*callback)(value *);
    public:
        value();
        value(std::string);

        void addSubscriber(uint8_t id);
        void rmSubscriber(uint8_t id);

        void set( std::string );
        std::string get();

        void setOnChange(bool);

//        void setCallback( void (*f)( value * ));
        void setCallback( void (*f)(uint8_t, std::string ));

        void display();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

    struct value* newClass();
    void display(struct value*);

#ifdef __cplusplus
}
#endif

#endif // _TESTING
