#define _CRT_SECURE_NO_WARNINGS
#define PAUSE system("pause")
#define CLS system("cls")
#define FLUSH clearBuffer()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


//Prototypes
void clearBuffer();
void getFloat(char[], float* f);
void getInt(char[], int* i);


void clearBuffer()
{
	while (getchar() != '\n');
}//end clearBuffer

void getFloat(char message[], float* f)
{
	char success;

	do
	{
		success = 'Y';
		printf("%s", message);

		if (scanf("%f", f) == 0)
		{
			printf("Invalid numeric data. . ."); FLUSH;
			PAUSE;

			success = 'N';
		}


	} while (success == 'N');
}

void getInt(char message[], int* i)
{
	char success;
	do
	{
		success = 'Y';

		printf("%s", message);

		if (scanf("%i", i) == 0)
		{
			printf("Invalid numeric data. . .\n"); FLUSH;
			PAUSE;

			success = 'N';
		}


	} while (success == 'N');

	return;

}
