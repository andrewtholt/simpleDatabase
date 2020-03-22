#include <stdlib.h>
#include <stdbool.h>

#include "set.h"

struct set *setNew(int s) {
    int *n = (int *)malloc(s * sizeof(int));

    struct set *p = (struct set *)malloc(sizeof(struct set));
    memset(p,0,sizeof(struct set));

    p->data = n;
    p->size = s;
}

void setAdd(struct set *p, int n) {
    int m = -1;
    for(int i=0; i < p->size;i++) {
        if ( p->data[i] == 0) {
            m = i;
        } else if( p->data[i] == n ) {
            return;
        }
    }
    if( m > 0) {
        p->data[m] = n;
    }
}

bool setContains(const struct set *p, int n) {
    bool c = false;

    for(int i=0; i < p->size;i++) {
        if( p->data[i] == n ) {
            c = true;
            break;
        } else {
            c = false;
        }
    }
    return c;
}

/*
void remove( struct set *p, int n) {
}
*/



