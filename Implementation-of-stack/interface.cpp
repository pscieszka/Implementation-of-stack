#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "interface.h"
#include "student.h"

const char* tab[] = {
	"1. Push",
	"2. Pop",
	"3. Clear",
	"4. Find",
	"5. Finish"

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
	scanf_s("%s", &nazwisko); // error handle
	printf("\nPodaj wiek:");
	scanf_s("%d", &wiek);
	printf("\nPodaj kierunek studiow (0-Informatyka, 1-Matematyka, 2-Fizyka):");
	scanf_s("%d", &kierunekStudiow);


}
