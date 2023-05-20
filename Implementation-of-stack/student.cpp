#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"

void* studentInit(char* nazwisko2, int  wiek2, kierunek kierunekStudiow2) {
	student* studentPtr = (student*)malloc(sizeof(student));
	if (studentPtr) {
		strcpy_s(studentPtr->nazwisko, sizeof(studentPtr->nazwisko), nazwisko2);
		studentPtr->wiek = wiek2;
		studentPtr->kierunekStudiow = kierunekStudiow2;
	}
	return (void*)(studentPtr);
}
void studentFree(void* ptr) {
	student* studentPtr = (student*)ptr;
	if (studentPtr) free(studentPtr);
}

void* studentPush(char* nazwisko, int  wiek, kierunek kierunekStudiow) {

	return studentInit(nazwisko, wiek, kierunekStudiow);
}

void  studentPrint(void* ptr) {
	student* studentPtr = (student*)ptr;
	if (studentPtr) {
		printf("Nazwisko: %s\n", studentPtr->nazwisko);
		printf("Wiek: %d\n", studentPtr->wiek);
		printf("Kierunek: %d\n", studentPtr->kierunekStudiow);
	}
}