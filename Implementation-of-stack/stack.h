#pragma once


typedef struct stack{
    void *dataPtr;
    stack* next;
} stack;

stack* stackPush(void* ptr);
stack stackPop();
