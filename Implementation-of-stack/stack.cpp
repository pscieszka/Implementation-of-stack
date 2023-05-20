#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"
#include "stack.h"


freeData ptrFree;
stack* top = NULL;

void stackInit(freeData ptrFree2) {
	top = NULL;
	ptrFree = ptrFree2;
}
void stackFree() {
	stack* curr =top;
	stack* next = NULL;

	while (curr != NULL) {
		(*ptrFree)(curr->dataPtr);
		next = curr;
		curr = curr->next;
		free(next);
	}
	top = NULL;
}

stack* stackPush(void* ptr) {
	stack* curr = (stack*)malloc(sizeof(stack));
	if (!curr)
		return NULL;

	curr->dataPtr = ptr;
	
	curr->next = top;
	top = curr;

	return curr;
}

stack stackPop() {
	stack popped;
	popped.dataPtr = NULL;
	popped.next = NULL;


	stack* poppedNode = top;
	popped.dataPtr = poppedNode->dataPtr;

	top = top->next;
	poppedNode->next = NULL;
	free(poppedNode);


	return popped;
}

stack* stackTop() {
	return top;
}