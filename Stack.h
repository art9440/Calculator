#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H
#define STACK struct stack
#include <malloc.h>
#include <stdio.h>

STACK{
    float value;
    STACK * next;
};

STACK* create(float value){
    STACK *elem;
    elem =(STACK*)malloc(sizeof (STACK));
    elem -> value = value;
    elem -> next = NULL;
    return elem;
}
#endif