#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"


void *studentInit(student* ob, int wiek, char nazwisko, kierunek kierunekStudiow)
{
	student* ob = (student*)malloc(sizeof(student));

	ob->wiek = wiek;
	ob->nazwisko = NULL;
	ob->nazwisko = (char*)malloc(2 * sizeof(char));
	
	ob->nazwisko[0] = str;
	ob->nazwisko[1] = '\0';
	ob->kierunekStudiow = kierunekStudiow;
	return (void*)(ob);
}

void studentFree(student* ob)
{
	if (ob->nazwisko)
		free(ob->nazwisko);
	ob->nazwisko = NULL;
}

void studentPrint(student* ob)
{
	if (ob->nazwisko)
	{
		printf("Nazwisko: %s\n", ob->nazwisko);
		printf("Wiek: %d\n", ob->wiek);
		switch (ob->kierunekStudiow)
		{
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
			printf("Nieznany kierunek studiow\n");
			break;
		}
	}
}

int studentAge() {
	int wiek;
	while (true) {
		printf("Podaj wiek studenta: ");
		if (scanf_s("%d", &wiek) == 1 && wiek > 0) {
			break;
		}
		printf("Niepoprawny wiek. Wprowadz liczbe calkowita wieksza od 0.\n");
	}
	return wiek;

}