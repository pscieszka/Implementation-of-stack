#pragma once

#pragma warning (disable : 4996)

typedef struct stack{
    void *dataPtr;
    stack* next;
} stack;

typedef void(*freeData)(void* ptr);
typedef int (compData)(void* dataPtr, void* searchData);

void stackInit(freeData ptrFree2);
void stackFree();
stack* stackPush(void* ptr);
stack stackPop();
stack* stackTop();
void* stackSearch(void* searchData, compData ptrComp, int firstEntry);
void stackSave(const char* filename);
void stackRead(const char* filename);
