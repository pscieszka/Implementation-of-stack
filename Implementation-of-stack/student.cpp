#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"

void* studentInit(char* nazwisko2, int  wiek2, kierunek kkierunekStudiow2) {
	student* studentPtr = (student*)malloc(sizeof(student));
	if (studentPtr) {
		strcpy(studentPtr->nazwisko, nazwisko2);
		studentPtr->wiek = wiek2;
		studentPtr->kierunekStudiow = kkierunekStudiow2;
	}
	return (void*)(studentPtr);
}
void* studentPush(char* nazwisko, int  wiek, kierunek kierunekStudiow) {

}