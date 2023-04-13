typedef struct
{
	char name[10];
	int score;


}WINNER;

void fillTopTenScores(WINNER topTenScores[])
{//Yasmeen
	for (int i = 0; i < 10; i++)//place default values in array
	{
		strcpy(topTenScores[i].name, "NULL");
		topTenScores[i].score = 0;
	}
}