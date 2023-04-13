//copy and paste this code into your c file
#include "Prototypes.h"
#include "Instructions.h"
#include "ShipStruct.h"
#include "WinnerStruct.h"
#include "Board.h"
#include "Functionality.h"

//Prototypes
void displayMainMenu();
int getSelection();
void quitGame();
void saveGame(SHIP battleships[], char invisibleBoard[][10], char gameBoard[][10], char usedCoords[][4], int eSize, int missileCount);
void loadGame(SHIP battleships[], char invisibleBoard[][10], char gameBoard[][10], char usedCoords[][4], int* eSize, int* missileCount);
void fillArrays(char invisibleBoard[][10], char gameBoard[][10]);
void fillShipArray(SHIP battleships[]);
void playGame(WINNER topTenScores[]);
void loadScores(WINNER topTenScores[]);
void displayScores(WINNER topTenScores[]);
void saveScore(WINNER topTenScores[], int missileCount, char name[]);

main()
{
	WINNER topTenScores[10];
	fillTopTenScores(topTenScores);
	loadScores(topTenScores);

	int selection = 0;//holds user selection for menu

	do
	{
		CLS;
		selection = getSelection(); FLUSH;
		switch (selection)
		{
		case 1://play game

			playGame(topTenScores);
			break;

		case 2:  //view top ten scores
			displayScores(topTenScores);
			break;

		case 3:  //display instructions
			CLS;
			gameInstructions();
			PAUSE;
			break;

		case 4:  //quit the program
			quitGame();
			break;

		default:
			printf("\nPLEASE ENTER A VALID SELECTION.\n\n"); FLUSH;
			break;
		}// end switch

	} while (selection != 4);
}

void displayMainMenu()
{//Yasmeen
	printf("\n");
	printf("BATTLESHIP\n");
	printf("----------\n");
	printf("1. PLAY\n");
	printf("2. TOP 10 SCORES\n");
	printf("3. HOW TO PLAY\n");
	printf("4. QUIT\n\n");

	printf("Enter Selection: ");


	return;
}//end of displayMainMenu

int getSelection()
{//Yasmeen
	int result;
	displayMainMenu();
	scanf("%d", &result);

	return result;
}// end of getSelection

void quitGame()
{//Yasmeen

	printf("\nTHANK YOU FOR PLAYING BATTLESHIP.\n\n");

}

void saveGame(SHIP battleships[], char invisibleBoard[][10], char gameBoard[][10], char usedCoords[][4], int eSize, int missileCount)
{//Yasmeen

	FILE* ptr = fopen("save.bin", "wb");//open (or create on 1st run) a file to save game

	if (ptr == NULL)//error and exit if file can't be opened
	{
		("ERROR: File could not be opened. . .");
		PAUSE;
		exit(-1);//hard exit

	}//end if



	//writing to save file

	fwrite(&eSize, sizeof(int), 1, ptr);//save eSize
	fwrite(&missileCount, sizeof(int), 1, ptr);//save missileCount
	fwrite(battleships, sizeof(SHIP), 5, ptr);//save battleships
	fwrite(invisibleBoard, sizeof(char), 100, ptr);//save invisibleBoard
	fwrite(gameBoard, sizeof(char), 100, ptr);//save gameBoard
	fwrite(usedCoords, sizeof(usedCoords[0]), eSize, ptr);//save usedCoords



	printf("\n\nGame has been saved . . .\n");
	fclose(ptr);//close bin file

}

void loadGame(SHIP battleships[], char invisibleBoard[][10], char gameBoard[][10], char usedCoords[][4], int* eSize, int* missileCount)
{//Yasmeen
	FILE* ptr = fopen("save.bin", "rb");//open bin file with data
	char choice;



	if (ptr == NULL) //error and exit if file can't be opened
	{

		return;

	}



	do
	{
		CLS;
		printf("Previous game found. . . Reload game? (Y/N): ");//ask user if they'd like to reload previously saved data
		choice = toupper(getc(stdin)); FLUSH;// get choice

		switch (choice)
		{
		case 'Y'://"yes"
			//fread(eSize, sizeof(int), 1, ptr);
			//fread(autoInventory, sizeof(AUTO), *eSize, ptr);

			fread(eSize, sizeof(int), 1, ptr);//load eSize
			fread(missileCount, sizeof(int), 1, ptr);//load missileCount
			fread(battleships, sizeof(SHIP), 5, ptr);//load battleships
			fread(invisibleBoard, sizeof(char), 100, ptr);//load invisibleBoard
			fread(gameBoard, sizeof(char), 100, ptr);//load gameBoard
			fread(usedCoords, sizeof(usedCoords[0]), *eSize, ptr);//load usedCoords


			printf("\nData Restored . . .\n\n");
			PAUSE;

			break;
		case 'N'://"no"
			break;

		default://invalid choice
			printf("\nPlease enter a valid selection. . . \n\n");
			PAUSE;
			break;
		}

	} while (choice != 'Y' && choice != 'N');// while an invalid choice is entered

	fclose(ptr);

}

void fillArrays(char invisibleBoard[][10], char gameBoard[][10])
{//Yasmeen
	//filling both arrays with default character
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			invisibleBoard[i][j] = '-';

	for (int y = 0; y < 10; y++)
		for (int z = 0; z < 10; z++)
			gameBoard[y][z] = '-';

}

void fillShipArray(SHIP battleships[])
{//Yasmeen
	//adding ships to the program, then putting them into 1D array 'battleships'
	SHIP baby = { "Baby", 2, 0,'B', 'Y', 0, 0, 0 };
	SHIP simple = { "Simple", 3, 0,'S', 'Y', 0, 0, 0 };
	SHIP rugged = { "Rugged", 3, 0, 'R', 'Y', 0, 0, 0 };
	SHIP valencia = { "Valencia", 4, 0, 'V', 'Y', 0, 0, 0 };
	SHIP giant = { "Giant", 5, 0, 'G', 'Y', 0, 0, 0 };// name of ship, length, current hits, letter, floating status, x-coord, y-coord, direction

	battleships[0] = baby;
	battleships[1] = simple;
	battleships[2] = rugged;
	battleships[3] = valencia;
	battleships[4] = giant;
}

void playGame(WINNER topTenScores[])
{//Yasmeen
	srand((unsigned)time(NULL));//seed rand

	SHIP battleships[5];
	char invisibleBoard[10][10] = { '0' };//gameboard to place ships
	char gameBoard[10][10] = { '0' };//gameboard to display


	char letCoord;//stores letter input
	char numCoord;//stores number input

	char usedCoords[100][4] = { 0 };//keeps track of the coordinates already used; used within getCoord() function to test if entered coordinate is a duplicate
	int eSize = 0;//keeps track of how many coordinates are stored in usedCoords


	int missileCount = 0;//keeps track of how many missiles have been fired

	char winnerName[20];//used to save name when win occurs
	WINNER placeholderArray[9];


	fillArrays(invisibleBoard, gameBoard);//fill arrays with -
	fillShipArray(battleships);//put ships in ship array


	placeTheShips(invisibleBoard, battleships);//randomly places ships onto invisible board
	loadGame(battleships, invisibleBoard, gameBoard, usedCoords, &eSize, &missileCount);

	char success = 'N';//flag that signals if good coordinate was entered within getCoord()
	do
	{
		do
		{
			displayGameBoard(gameBoard, battleships, missileCount);//displays gameBoard; updates for every loop
			int isAWin = winTheGame(battleships, winnerName);//check if game has been won before asking for coordinates

			if (isAWin == 0)//if game has not been won yet
			{
				success = getCoord(usedCoords, &eSize, &letCoord, &numCoord);//gets a coordinate (success receives flag for getCoord)
			}
			else
			{
				success = 'W';//set flag to indicate game has been won
			}

		} while (success == 'N');//do while coordinate is invalid

		if (success == 'Y')//fire a missile if user enters good coordinate
		{
			fireMissile(letCoord, numCoord, invisibleBoard, gameBoard, battleships, &missileCount);//fires a missile at given coordinate, sees if a ship was hit, and 'sinks' a ship if ship hits equals ship length
		}
		else if (success == 'Q')//save game and quit if user quits
		{
			saveGame(battleships, invisibleBoard, gameBoard, usedCoords, eSize, missileCount);
			quitGame();
			PAUSE;


		}
		else if (success == 'W')//quit game if user wins
		{
			saveScore(topTenScores, missileCount, winnerName);
			quitGame();
			PAUSE;
		}

	} while (success != 'Q' && success != 'W');//repeat while user doesn't want to quit and game hasn't been won

}

void saveScore(WINNER topTenScores[], int missileCount, char name[])
{//Yasmeen
	WINNER newWinner;// make a new struct to hold user info
	WINNER placeholderArray[11];
	fillTopTenScores(placeholderArray);

	strcpy(newWinner.name, name);//copy winner name to struct
	newWinner.score = missileCount;//copy winner score to struct


	char repeat = 'Y';

	for (int i = 0; i < 10; i++)//iterate through top ten scores
	{
		if (repeat == 'Y')//if new user hasn't been placed into top ten scores yet
		{
			if (newWinner.score <= topTenScores[i].score || topTenScores[i].score == 0)//if new score is bigger than current score in the top ten scores or current score is the default 0
			{

				strcpy(placeholderArray[i].name, newWinner.name);//copy winner name to placeholder array at index 0
				placeholderArray[i].score = newWinner.score;//copy winner score to placeholder array at index 0

				int j = i + 1;
				while (j < 10)//this loop copies topTenScores[i] and all names and scores beneath it to the placeholder array
				{
					strcpy(placeholderArray[j].name, topTenScores[j - 1].name);
					placeholderArray[j].score = topTenScores[j - 1].score;
					j++;
				}

				for (int k = i; k < 10; k++)// the placeholder array, which now contains the winner info and all the indexes below it, are fed back into topTenScores
				{
					topTenScores[k] = placeholderArray[k];
				}


				repeat = 'N';//raise flag
			}
		}


	}


	FILE* ptr = fopen("scores.bin", "wb");//open (or create on 1st run) a file to save autos

	if (ptr == NULL)//error and exit if file can't be opened
	{
		("ERROR: File could not be opened. . .");
		PAUSE;
		exit(-1);//hard exit

	}//end if



	//writing to scores file
	fwrite(topTenScores, sizeof(WINNER), 10, ptr);//save scores

	fclose(ptr);


}

void loadScores(WINNER topTenScores[])
{//Yasmeen
	FILE* ptr = fopen("scores.bin", "rb");//open bin file with data

	fread(topTenScores, sizeof(WINNER), 10, ptr);//load top ten scores

	fclose(ptr);
}

void displayScores(WINNER topTenScores[])
{//Yasmeen
	CLS;
	printf("\n%29s\n\n", "TOP TEN SCORES");

	printf("\tNAME\t\t\tSCORE\n");
	printf("\t----\t\t\t-----");



	for (int i = 1; i <= 10; i++)
	{
		printf("\n");
		printf("%i.\t%-10s\t\t%3i", i, topTenScores[i - 1].name, topTenScores[i - 1].score);

	}

	printf("\n\n\n");


	PAUSE;
}