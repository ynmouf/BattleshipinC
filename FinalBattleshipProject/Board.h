//This file contains all functions associated with filling the invisible board with the ships and displaying the gameBoard


//Prototypes
void displayGameBoard(char gameboard[][10], SHIP battleships[], int missileCount);
void placeTheShips(char invisibleBoard[][10], SHIP battleships[]);
int doesItFit(char invisibleBoard[][10], SHIP battleship, int x, int y, int direction);
void positionAssign(int* x, int* y, int* direction);
void statPrinter(SHIP battleship, int i, int missileCount);



void displayGameBoard(char gameboard[][10], SHIP battleships[], int missileCount)
{//Yasmeen
	CLS;

	printf("\n");
	printf("    ");

	printf("- BATTLESHIP -");

	char boardLetters[] = { 'A', 'B', 'C','D', 'E', 'F','G', 'H', 'I', 'J' };// size = 10// this is for easy loading into the visible gameboard


	printf("\n\n");
	printf("  ");

	for (int num = 0; num < 10; num++)//display top row of numbers 0-9
	{
		printf("%i", num);
		printf(" ");
	}

	printf("\n");

	for (int i = 0; i < 10; i++)//display rows
	{
		printf("%c ", boardLetters[i]);//prints letters that represent rows

		for (int j = 0; j < 10; j++)// display columns
		{
			printf("%c ", gameboard[i][j]);
		}

		statPrinter(battleships[i], i, missileCount);//prints one row per iteration of stat column besides gameBoard

		printf("\n");
	}

	printf("\n");
}//end of displayGameBoard

void placeTheShips(char invisibleBoard[][10], SHIP battleships[])//places all ships on the board
{//Yasmeen

	for (int i = 0; i < 5; i++)//for all 5 ships
	{
		//necessary info to place ship; will be manipulated by the postionAssign function
		int x;
		int y;
		int direction;

		int errorCode;//number returned by doesItFit to signal if there is enough space for ship; 0 means success & -1 means failure
		do
		{
			positionAssign(&x, &y, &direction);//assign x coord, y coord, and direction

			errorCode = doesItFit(invisibleBoard, battleships[i], x, y, direction);//check if ship will fit in chosen spot

		} while (errorCode == -1);//repeat while ship doesn't fit




		//placing the letters for each ship either horizontally or vertically
		if (direction == 0)
		{
			for (int space = 0; space < battleships[i].length; space++)//iterate by ship length
			{


				invisibleBoard[x][y + space] = battleships[i].letter;// place letters horizontally


			}
		}
		else
		{
			for (int space = 0; space < battleships[i].length; space++)
			{


				invisibleBoard[x + space][y] = battleships[i].letter;//place letters vertically 

			}

		}

		//saving coordinate info to ship
		battleships[i].x = x;
		battleships[i].y = y;
		battleships[i].direction = direction;



	}//end outer for





}

int doesItFit(char invisibleBoard[][10], SHIP battleship, int x, int y, int direction)//assigns a spot on the board to ship and checks if a ship fits
{//Yasmeen

	char success = 'Y'; // flag that signals success; will change to 'N' if space for ship not found


	if (direction == 0)//horizontal check
	{
		for (int space = 0; space < battleship.length; space++)//tells loop to check spaces in horizontal direction for as long as the ship is
		{
			if (invisibleBoard[x][y + space] != '-' || y + battleship.length > 10)//if one of the spaces isn't empty or ship will spill onto next row, the flag will be raised
			{
				success = 'N';//raise fail flag

			}//end inner if 

		}//end for

	}//end outer if

	else //vertical check
	{
		for (int space = 0; space < battleship.length; space++)//tells loop to check spaces in vertical direction for as long as the ship is
		{
			if (invisibleBoard[x + space][y] != '-')//if one of the spaces isn't empty, the flag will be raised
			{
				success = 'N';//raise fail flag

			}//end if

		}//end for

	}//end else statement	


	if (success == 'N')
	{
		return -1;//error code
	}
	else
	{
		return 0;//success code
	}






}

void positionAssign(int* x, int* y, int* direction)
{//Yasmeen

	//assigning upper and lower bounds for coordinate and direction picking
	int UB = 9;
	int LB = 0;

	int dirUB = 1;
	int dirLB = 0;

	*x = LB + rand() % (UB - LB + 1);//random row
	*y = LB + rand() % (UB - LB + 1);//random column

	*direction = dirLB + rand() % (dirUB - dirLB + 1);// 0 will be horizontal, 1 vertical

	return;


}

void statPrinter(SHIP battleship, int i, int missileCount)
{//Yasmeen
	char status[20] = "Default";

	if (battleship.floating == 'Y')//if ship is floating "Floating" is printed
	{
		strcpy(status, "Floating");
	}
	else if (battleship.floating == 'N')//if ship is sunk "Sunk" is printed
	{
		strcpy(status, "Sunk");
	}


	if (i < 5)
	{
		printf("  %s Ship:\t%s", battleship.name, status);//prints status next to ship name
	}
	if (i == 5)
	{
		printf(" ");
	}
	if (i == 6)
	{
		printf("  Missiles Fired:  %i", missileCount);
	}
}