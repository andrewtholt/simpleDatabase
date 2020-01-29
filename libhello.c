/* libhello.c - demonstrate library use. */

#include <stdio.h>

void hello(void) {
  printf("Hello, library world.\n");
}

void order(int a, int b) {
    printf("a=%d\n",a);
    printf("b=%d\n",b);
}
