#pragma once


typedef struct stack{
    void *dataPtr;
    stack* next;
} stack;

typedef void(*freeData)(void* ptr);

void stackInit();
stack* stackPush(void* ptr);
stack stackPop();
