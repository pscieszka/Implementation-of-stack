#pragma once
enum kierunek
{
	INFORMATYKA,
	MATEMATYKA,
	FIZYKA
};

	struct student
	{
		char nazwisko[512];
		int wiek;
		kierunek kierunekStudiow;
	};

	void* studentInit(char* nazwisko2, int  wiek2, kierunek kierunekStudiow2);
	void  studentFree(void* ptr);
	void* studentPush(char* nazwisko, int  wiek, kierunek kierunekStudiow);
	void  studentPrint(void* ptr);

	


