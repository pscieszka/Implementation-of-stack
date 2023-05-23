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
	if (fopen_s(&file, filename, "rb") != 0) {
		printf("Error otwierania pliku.\n");
		return;
	}

	// Ustawienie wskaŸnika na koniec pliku
	if (fseek(file, 0, SEEK_END) != 0) {
		printf("Error ustawiania wskaŸnika na koniec pliku.\n");
		fclose(file);
		return;
	}

	// Okreœlenie rozmiaru pliku
	long fileSize = ftell(file);
	if (fileSize == -1) {
		printf("Error okreœlania rozmiaru pliku.\n");
		fclose(file);
		return;
	}

	// Przesuniêcie wskaŸnika o jeden rekord wstecz
	int recordSize = sizeof(struct student);
	fseek(file, -recordSize, SEEK_END);

	// Odczytywanie danych wstecz i dodawanie ich do stosu
	while (fileSize > 0) {
		struct student* stud = (struct student*)malloc(recordSize);
		if (stud == NULL) {
			printf("Memory allocation error.\n");
			fclose(file);
			return;
		}

		if (fread(stud, recordSize, 1, file) != 1) {
			printf("Error odczytywania danych z pliku.\n");
			free(stud);
			fclose(file);
			return;
		}

		stackPush(stud);

		// Przesuniêcie wskaŸnika o jeden rekord wstecz
		fseek(file, -2 * recordSize, SEEK_CUR);
		fileSize -= recordSize;
	}

	fclose(file);
}
