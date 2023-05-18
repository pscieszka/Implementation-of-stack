#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"
#include "stack.h"


static const stack* top = NULL;
void stackInit() {
}

stack* push(void* ptr) {
	stack* curr = (stack*)malloc(sizeof(stack));
	if (!curr)	return NULL;

}