#include <iostream>
#include <cstdlib>
int const SIZE= 4;

struct Stack
{
    int top=-1;
    unsigned capacity;
    int *array;
};

typedef Stack S;

