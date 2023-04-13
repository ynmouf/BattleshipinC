typedef struct
{
	char name[10];//name of ship

	int length;//length of ship (total hits needed to sink the ship)

	int hits;// current # of hits

	char letter;//what letter represents it

	char floating;//YES or NO

	int x;//row location
	int y;//column location
	int direction;// 0 for horizontal, 1 for vertical


}SHIP;

