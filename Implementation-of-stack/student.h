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
	void* studentPush(char* nazwisko2, int  wiek2, kierunek kierunekStudiow2);

	


