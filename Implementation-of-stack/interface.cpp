#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "interface.h"
#include "student.h"
#include "stack.h"

const char* tab[] = {
	"0. Push",
	"1. Pop",
	"2. Find",
	"3. Clear",
	"4. Show",
	"5. Read stack from file",
	"6. Save stack to file",
	"7. Read student to file",
	"8. Save student to file",
	"9. Finish"

};

const int menuSize = sizeof(tab) / sizeof(tab[0]);

void menu() {
	printf("Wybierz opcje:\n");
	for (int i = 0; i < menuSize; i++) {
		printf("%s\n", tab[i]);
	}
}

void push() {
	char nazwisko[512];
	int wiek;
	kierunek kierunekStudiow;
	printf("Podaj nazwisko:");
	scanf_s("%s",nazwisko, sizeof(nazwisko)); // error handle
	printf("\nPodaj wiek:");
	scanf_s("%d", &wiek);
	printf("\nPodaj kierunek studiow (0-Informatyka, 1-Matematyka, 2-Fizyka):");
	scanf_s("%d", &kierunekStudiow);
	void* ptr = studentPush(nazwisko, wiek, kierunekStudiow);
	if (!stackPush(ptr))
		printf("push error\n");
}

void pop() {
	if (stackTop() == NULL) {
		printf("Stos jest pusty.\n");
		return;
	}

	stack temp = stackPop();
	if (temp.dataPtr != NULL) {
		studentPrint(temp.dataPtr);
		studentFree(temp.dataPtr);
	}
}

void find() {
	char nazwisko2[128];
	int found = 0;
	printf("Podaj nazwisko:");
	scanf_s("%s", nazwisko2, sizeof(nazwisko2));
	student searchData;
	memset(&searchData, 0, sizeof(student));
	strcpy_s(searchData.nazwisko, sizeof(searchData.nazwisko), nazwisko2);
	
	void* ptrData = stackSearch(&searchData, studentSearch, 1);

	if (ptrData) {
		printf("Znaleziono studenta:\n");
		found = 1;
		studentPrint(ptrData);
	}

	while (ptrData) {
		ptrData = stackSearch(&searchData, studentSearch, 0);
		if (ptrData) {
			printf("Znaleziono studenta:\n");
			found = 1;
			studentPrint(ptrData);
		}
	}
	if (!found)	printf("\n Nie zaleziono studenta.\n");
}

void clear()
{
	stackFree();
}
void show() {
	stack* ptr = stackTop();
	if (!ptr) printf("Stos jest pusty\n");
	while (ptr) {
		studentPrint(ptr->dataPtr);
		ptr = ptr->next;
	}
		
	
	
}

void readStudent() {
	void* ptr = loadStudentFromFile("student.bin");
	if (ptr != NULL) {
		stackPush(ptr);
		studentPrint(ptr);
	}
}

void saveStudent() {
	stack* curr = stackTop();
	if (curr == NULL) {
		printf("No student data available to save.\n");
		return;
	}

	void* ptr = curr->dataPtr;
	stackPop();

	saveStudentToFile("student.bin", ptr);
	studentPrint(ptr);
	free(ptr);
}
