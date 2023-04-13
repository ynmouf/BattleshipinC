//Functions that make interactive gameplay possible
#define SHIPS 5

//Prototypes
char getCoord(char usedCoords[][4], int* eSize, char* letCoord, char* numCoord);//gets a valid coordinate and keeps track of coords used
int checkCoord(char* coord);//used in conjunction with getCoord() to ensure validity of user input
void fireMissile(char letCoord, char intCoord, char invisibleBoard[][10], char gameBoard[][10], SHIP battleships[], int* missileCount);//performs conversion on input and calls hitOrMiss() & sinkShip()
void hitOrMiss(int row, int column, char invisibleBoard[][10], char gameBoard[][10], SHIP battleships[]);//checks what is located at missile location and replaces the dash with an H or M
void sinkShip(SHIP battleships[], char gameBoard[][10]);//checks if ship has been sunk and changes ship status if so
int winTheGame(SHIP battleships[], char winnerName[]);//checks if all ships have been sunk and displays winning message and records name if so
char isADuplicate(char usedCoords[][4], int eSize, char* coord);//checks if enterd coordinate is a duplicate

char getCoord(char usedCoords[][4], int* eSize, char* letCoord, char* numCoord)
{//Brent, Yasmeen
    char coord[10];//will store inputted string

    char success = 'Y';//flag to indicate successful input

    printf("Enter coordinate to fire a missile (or 'QQ' to quit): ");
    scanf("%s", &coord); FLUSH;//get user input


    char duplicate = isADuplicate(usedCoords, *eSize, &coord);


    if (strcmp(coord, "qq") == 0 || (strcmp(coord, "QQ") == 0))//if user quits game
    {
        success = 'Q';//quit flag
    }
    else if (checkCoord(&coord) == 0 || strlen(coord) > 2)//if coordinate entry is invalid
    {
        printf("\nAn invalid coordinate was entered - try again\n\n");
        PAUSE;
        success = 'N';//getting a coordinate was not successful
    }
    else if (duplicate == 'Y')//if coordiate was a duplicate
    {
        printf("\nYou've already entered this coordinate\n\n");
        PAUSE;
        success = 'N';//getting a coordinate was not successful
    }


    else//successful entry
    {

        // printf("\nThe first portion of the coordinate is: %c, the second portion of the coordinate is: %c\n\n", toupper(coord[0]), coord[1]);

        for (int j = 0; j < strlen(coord); j++)//iterate through coord, adding each index to usedCoords at current eSize
        {
            usedCoords[*eSize][j] = coord[j];
        }


        //assign each individual part of coordinate to functions for easy access later
        *letCoord = coord[0];//assign first index to letCoord
        *numCoord = coord[1];// assign second index to numCoord

        (*eSize)++;//increase eSize of usedCoords
    }

    return success;//return value of success flag


}//end of getCoord

int checkCoord(char* coord)
{//Yasmeen
    if (toupper(coord[0]) < 'A' || toupper(coord[0]) > 'J')//if first character doesn't equal a letter from A to J
    {
        return 0;//fail code
    }

    if (coord[1] < '0' || coord[1] > '9')// if second character doesn't equal a letter from 1 to 9
    {
        return 0;//fail code
    }



}//end of checkCoord

void fireMissile(char letCoord, char intCoord, char invisibleBoard[][10], char gameBoard[][10], SHIP battleships[], int* missileCount)
{//Yasmeen
    int row = toupper(letCoord) - 65;//converts letter input to accurate row location (ex. C gets converted to 2 because row C is row 2)

    int column = intCoord - '0';// converts char number to an int; retains same value

    hitOrMiss(row, column, invisibleBoard, gameBoard, battleships);//checks if ship is located at invisibleBoard[row][column] and places an H or an M depending on result
    sinkShip(battleships, gameBoard);//replaces H's with the ship's letters and changes float status of ship if a ship's hits equals its length

    (*missileCount)++;//increase missileCount

}

void hitOrMiss(int row, int column, char invisibleBoard[][10], char gameBoard[][10], SHIP battleships[])
{//Yasmeen
    if (invisibleBoard[row][column] == '-')//if no ship located
    {
        gameBoard[row][column] = 'M';//miss
    }
    if (invisibleBoard[row][column] != '-')//if a ship is located
    {
        for (int i = 0; i < 5; i++)//for all 5 ships
        {
            if (battleships[i].letter == invisibleBoard[row][column])//check which ship letter was hit
            {
                gameBoard[row][column] = 'H';//replace that location with an H
                battleships[i].hits++;//increase the hit count of the ship that was hit
            }
        }
    }
}

void sinkShip(SHIP battleships[], char gameBoard[][10])
{//Yasmeen
    for (int i = 0; i < 5; i++)//for all 5 ships
    {
        if (battleships[i].hits == battleships[i].length)//if any of the ship's hits equals its length
        {
            battleships[i].floating = 'N';//change floating status

            if (battleships[i].direction == 0)//if ship was placed horizontally
            {
                for (int space = 0; space < battleships[i].length; space++)//iterate by ship length
                {


                    gameBoard[battleships[i].x][battleships[i].y + space] = battleships[i].letter;//place the ship's letters horizontally in place of the H's


                }
            }
            else//if ship was placed vertically
            {
                for (int space = 0; space < battleships[i].length; space++)//iterate by ship length
                {


                    gameBoard[battleships[i].x + space][battleships[i].y] = battleships[i].letter;//place the ship's letters vertically in place of the H's

                }

            }



        }
    }
}

int winTheGame(SHIP battleships[], char winnerName[])
{//Yasmeen
    int sunkShipCounter = 0;//counter
    for (int i = 0; i < 5; i++)//for all 5 ships
    {
        if (battleships[i].floating == 'N')//if ship has been sunk
        {
            sunkShipCounter++;//increase counter
        }
    }

    if (sunkShipCounter == 5)//if all ships have been sunk
    {
        printf("\nCongratulations, you sunk all the ships!\n\n");//win message
        printf("Enter your name: ");

        scanf("%s", winnerName); FLUSH;//get winnerName

        return 1;//win code
    }
    else
    {
        return 0;//no win code
    }
}

char isADuplicate(char usedCoords[][4], int eSize, char* coord)
{//Yasmeen
    char duplicateFlag = 'N';//flag that signals if entered coord has been entered already
    for (int i = 0; i < eSize; i++)//iterating for size of array that contains used coordinates (going to compate entered coordinate with every coordinate entered in the past)
    {
        if (tolower(coord[0]) == usedCoords[i][0] && coord[1] == usedCoords[i][1])//compares first index of coordinate with first part of past coordinates and repeats for second index
        {
            duplicateFlag = 'Y';//if equal, raise flag
        }
    }

    return duplicateFlag;
}
