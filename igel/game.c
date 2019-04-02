typedef struct token
{
	enum colour col;
};

typedef struct square
{
	enum stype type;
	
	token * stack
	
	int numTokens
	
};




typedef struct player
{
	char name[20]
	enum colour col
	int numTokenLastCol
};

typedef struct token
{
	enum colour col;
};








void place_token(square board[NUM_ROWS][NUM_COLUMNS],player players[], int numPlayers)
{
//the min no. of tokens
int minNumofTokens=0;
int selectedSquare=0;

for(int i=0; i<4; i++)
{
	
	for(int j=0; j<numPlayers; j++)
	{
		printf("Player %d please select a square\n",j);
		scanf("%d, &selectedSquare")
		
		
		board[selectedSquare][0].stack=(token *)malloc(sizeof(token));
		board[selectedSquare][0].stack->col=players[j].col;
		board[selectedSquare][0].numTokens++;
		
		if (((numPlayers * i)+j+1)%NUM_ROWS==0)
		minNumoofTokens++;
	}
	
}

}
