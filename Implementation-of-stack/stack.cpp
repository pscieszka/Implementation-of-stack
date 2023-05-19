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
	stack* ptr =top;
	stack* temp = NULL;
	while()
}

stack* push(void* ptr) {
	stack* curr = (stack*)malloc(sizeof(stack));
	if (!curr)	return NULL;

}