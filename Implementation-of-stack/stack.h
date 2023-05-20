#pragma once


typedef struct stack{
    void *dataPtr;
    stack* next;
} stack;

typedef void(*freeData)(void* ptr);

void stackInit(freeData ptrFree2);
void stackFree();
stack* stackPush(void* ptr);
stack stackPop();
stack* stackTop();

