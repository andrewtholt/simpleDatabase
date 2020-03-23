#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct set {
    int size;
    int count;
    int *data;
};

struct set *setNew(int size);

void setAdd(struct set *p, int n);

bool setContains(const struct set *p, int n);

void setRemove(struct set *p, int n);

int setCount(const struct set *p);

void setDisplay(const struct set *p);
