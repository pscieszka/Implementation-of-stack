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
void* stackSearch(void* searchData, compData ptrComp, int firstEntry) {
	static stack* ptr;
	stack* ptr2 = NULL;
	if (firstEntry) {
		ptr = top;
	}
	if (ptr == NULL) {
		return NULL;
	}
	while (ptr) {
		if (!(*ptrComp)(ptr->dataPtr, searchData)) {
			ptr = ptr->next;
		}
		else {
			ptr2 = ptr;
			ptr = ptr->next;
			return ptr2->dataPtr;
		}
	}
	return NULL;
	

}
void stackSave(const char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "wb") != 0)
	{
		printf("Error opening file for writing.\n");
		return;
	}

	stack* curr = top;
	while (curr != NULL) {
		struct student* stud = (struct student*)(curr->dataPtr);
		fwrite(stud, sizeof(struct student), 1, file);
		curr = curr->next;
	}

	fclose(file);
	stackFree();
}

void stackRead(const char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0)
	{
		printf("Error otwierania pliku.\n");
		return;
	}

	stackFree();

	struct student* stud = (struct student*)malloc(sizeof(struct student));
	if (stud == NULL)
	{
		printf("Memory allocation error.\n");
		fclose(file);
		return;
	}

	while (fread(stud, sizeof(struct student), 1, file) == 1) {
		stackPush(stud);

		stud = (struct student*)malloc(sizeof(struct student));
		if (stud == NULL)
		{
			printf("Memory allocation error.\n");
			fclose(file);
			return;
		}
	}

	free(stud);
	fclose(file);
}
