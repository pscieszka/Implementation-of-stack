#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"


bool studentInit(student* ob, int wiek, char* str, kierunek kierunekStudiow)
{
	ob->wiek = wiek;
	ob->nazwisko = NULL;
	size_t len = strlen(str);
	if (len)
	{
		ob->nazwisko = (char*)malloc((len + 1) * sizeof(char));
		if (!ob->nazwisko)
			return false;
		strcpy_s(ob->nazwisko, _msize(ob->nazwisko), str);
	}
	return true;
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