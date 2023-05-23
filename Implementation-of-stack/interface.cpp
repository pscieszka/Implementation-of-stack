#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "interface.h"
#include "student.h"
#include "stack.h"
#include "message.h"


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
	"9. Clear files",
	"10. Finish"

};

const int menuSize = sizeof(tab) / sizeof(tab[0]);

void menu() {
	printf("Wybierz opcje:\n");
	for (int i = 0; i < menuSize; i++) {
		if (tab[i] == "7. Read student to file")
			printf("7. Read student to file - zapis/odczyt maksymalnie 1 rekordu(read->stackPush, save->stackPop)\n");
		else
			printf("%s\n", tab[i]);
		
	}
}

void push() {
	char nazwisko[512];
	int wiek;
	kierunek kierunekStudiow;
	printf("Podaj nazwisko:");
	if (scanf_s("%s", nazwisko, sizeof(nazwisko)) != 1) { //zabezpiecznie przed za dlugim ciagiem znakow oraz inputem typu "abc abc"
		printf("Bledne dane: niepoprawne nazwisko\n");    //w przypadku spacji do zmiennej nazwisko zapisze sie ciag zankow przed pierwszym pojawieniem sie spacji
		while (getchar() != '\n') {}
		return;
	}
	while (getchar() != '\n') {}
	

	printf("\nPodaj wiek:");
	if (scanf_s("%d", &wiek) != 1 || wiek < 0 || wiek>200) { //wiek powienien byc wiekszy od 0 i mniejszy od 200, zabezpiecznie przed inputem innym niz int
		printf("Bledne dane: niepoprawny wiek\n");
		while (getchar() != '\n') {}
		return;
	}
	printf("\nPodaj kierunek studiow (0-Informatyka, 1-Matematyka, 2-Fizyka):");

	
	if(scanf_s("%d", &kierunekStudiow) != 1 || (kierunekStudiow != 0 && kierunekStudiow != 1 && kierunekStudiow != 2)) { //kierunek moze byc tylko 0,1 lub 2, zabezpiecznie przed inputem innym niz int
		printf("Bledne dane: niepoprawny kierunek studiow\n");
		while (getchar() != '\n') {}
		return;
	}
	void* ptr = studentPush(nazwisko, wiek, kierunekStudiow);
	if (!stackPush(ptr))
		messageFun(PUSH_ERROR);
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
	if (scanf_s("%s", nazwisko2, sizeof(nazwisko2)) != 1) { //analogiczne zabezpiecznie jak w funkcji push()
		printf("Bledne dane: niepoprawne nazwisko\n");
		while (getchar() != '\n') {}
		return;
	}
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

void readStack() {
	stackRead("stackdata.bin");
}

void saveStack() {
	stackSave("stackdata.bin");
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
		printf("Brak danych do zapisu.\n");
		return;
	}

	void* ptr = curr->dataPtr;
	stackPop();

	saveStudentToFile("student.bin", ptr);
	studentPrint(ptr);
	free(ptr);
}

void deleteFiles() {
	
	int flag = 0;
	if (remove("student.bin") != 0) {
		printf("Nie mozna usunac pliku student.bin (prawdopodobnie plik nie istnieje).\n");
		flag = 1;
	}

	
	if (remove("stackdata.bin") != 0) {
		printf("Nie mozna usunac pliku stackdata.bin (prawdopodobnie plik nie istnieje).\n");
		flag = 1;
	}
	if(!flag)
		printf("\nPliki poprawnie wyczyszczone\n\n");
}