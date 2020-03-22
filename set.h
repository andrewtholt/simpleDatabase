#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct set {
    int size;
    int *data;
};

struct set *setNew(int size);

void setAdd(struct set *p, int n);

bool setContains(const struct set *p, int n);

/*
void remove(struct set *p, int n);
*/



