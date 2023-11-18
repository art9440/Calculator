#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"


int main(){
    STACK * L;
    L = create(0);
    float value;
    scanf("%f", &value);
    while (value != EOF){
        STACK * p;
        p = create(value);
        scanf("%f", &value);
        push(L, p);
    }
    return 0;
}
