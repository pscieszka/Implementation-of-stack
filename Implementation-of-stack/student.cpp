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
int	studentSearch(void* currData, void* searchData) {
	student* curr = (student*)currData;
	student* search = (student*)searchData;
	if (strcmp(curr->nazwisko, search->nazwisko) == 0)
		return 1;
	return 0;
}
void  saveStudentToFile(const char* filename, void* ptr) {
	if (ptr == NULL)
	{
		printf("Cannot save NULL student pointer.\n");
		return;
	}

	struct student* stud = (struct student*)ptr;
	FILE* file;
	if (fopen_s(&file, filename, "wb") != 0)
	{
		printf("Error opening file for writing.\n");
		return;
	}
	

	fwrite(stud, sizeof(struct student), 1, file);
	fclose(file);
}


void* loadStudentFromFile(const char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0)
	{
		printf("Error opening file for writing.\n");
		return NULL;
	}

	struct student* stud = (struct student*)malloc(sizeof(struct student));
	if (stud == NULL)
	{
		printf("Memory allocation failed.\n");
		fclose(file);
		return NULL;
	}

	fread(stud, sizeof(struct student), 1, file);
	fclose(file);

	return stud;
}