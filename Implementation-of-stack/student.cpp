#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"
#include "message.h"

void* studentInit(char* nazwisko2, int  wiek2, kierunek kierunekStudiow2) {
	student* studentPtr = (student*)malloc(sizeof(student));
	if (studentPtr) {
		studentPtr->nazwisko = (char*)malloc((strlen(nazwisko2) + 1) * sizeof(char));
		if (!studentPtr->nazwisko) {
			free(studentPtr);
			return NULL;
		}
		strcpy_s(studentPtr->nazwisko, strlen(nazwisko2) + 1, nazwisko2);
		studentPtr->len = strlen(nazwisko2);
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
		switch (studentPtr->kierunekStudiow) {
		case INFORMATYKA:
			printf("Kierunek: Informatyka\n");
			break;
		case MATEMATYKA:
			printf("Kierunek: Matematyka\n");
			break;
		case FIZYKA:
			printf("Kierunek: Fizyka\n");
			break;
		default:
			printf("Kierunek: Nieznany\n");
			break;
		}
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
		printf("Nie mozna zapisac.\n");
		return;
	}

	student* stud = (student*)ptr;
	FILE* file;
	if (fopen_s(&file, filename, "wb") != 0)
	{
		messageFun(ALLOC_ERROR);
		return;
	}
	size_t size = strlen(stud->nazwisko) + 1;
	fwrite(&size, sizeof(size_t), 1, file);
	fwrite(stud->nazwisko, sizeof(char), size, file);
	fwrite(&(stud->len), sizeof(size_t), 1, file);
	fwrite(&(stud->wiek), sizeof(int), 1, file);
	fwrite(&(stud->kierunekStudiow), sizeof(kierunek), 1, file);

	fclose(file);
}


void* loadStudentFromFile(const char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0)
	{
		messageFun(FILE_OPEN_FAILED);
		return NULL;
	}

	student* stud = (student*)malloc(sizeof(student));
	if (stud == NULL)
	{
		fclose(file);
		messageFun(ALLOC_ERROR);
		return NULL;
	}

	size_t size;
	fread(&size, sizeof(size_t), 1, file);
	stud->nazwisko = (char*)malloc(size * sizeof(char)); //alokujemy pamiec dla skladowej strukutry 'nazwisko'
	if (!stud->nazwisko) {
		fclose(file);
		free(stud);
		messageFun(ALLOC_ERROR);
		return NULL;
	}

	fread(stud->nazwisko, sizeof(char), size, file);
	fread(&(stud->len), sizeof(size_t), 1, file);
	fread(&(stud->wiek), sizeof(int), 1, file);
	fread(&(stud->kierunekStudiow), sizeof(kierunek), 1, file);
	fclose(file);


	return stud;
}