#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "set.h"

struct set *setNew(int s) {
    int *n = (int *)malloc(s * sizeof(int));

    struct set *p = (struct set *)malloc(sizeof(struct set));
    memset(p,0,sizeof(struct set));

    p->data = n;
    p->size = s;
    p->count = 0;
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
        p->count++;
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

void setRemove( struct set *p, int n) {
    for(int i=0; i < p->size;i++) {
        if( p->data[i] == n ) {
            p->data[i] = 0;
            p->count--;

            if( p->count < 0 ) {
                p->size = 0;
            }

            break;
        }
    }
}

int setCount(const struct set *p) {
    return p->count;
}

void setDisplay(const struct set *p ) {
    printf("Set size : %4d\n", p->size);
    printf("Members  : ");
    if ( p->count == 0) {
        printf("Empty\n");
    } else {
        printf("%4d\n", p->count);
    }
    for(int i=0; i < p->size;i++) {
        if( p->data[i] != 0 ) {
            printf("%4d\n", p->data[i]);
        }
    }
    printf("=====\n");
}

