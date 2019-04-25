/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printLine();
     
void move_vertical (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum);
void move_adj(square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum, int roll);
void move_adjacent (square board[NUM_ROWS][NUM_COLUMNS], int row_increment, int col_increment, int roll);
void move_right (square board[NUM_ROWS][NUM_COLUMNS], int roll) ;
void obstacle(square board[NUM_ROWS][NUM_COLUMNS], int curr_column);
void move_sideways (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum);
void move_horizontal (square board[NUM_ROWS][NUM_COLUMNS], int roll);

//function for adding a token on top of a stack
struct stack_token * push(token *newtoken, struct stack_token *top){
    struct stack_token *curr = top;
    top = malloc(sizeof(stack_token));
    top->token = newtoken;				//the top token is assigned value of new token
    top->next = curr;
    return top;							//returns new top of stack which points to the newly added token
}

struct stack_elem *top = NULL;
struct stack_elem *curr = NULL;

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

void move_adjacent (square board[NUM_ROWS][NUM_COLUMNS],int row_increment,int col_increment, int roll) {
	int column=0;
	int row= roll;
	token * temp = board[row+row_increment][column].stack->token;									//temp is assigned the top token of the selected square
	stack_token * next = board[row+row_increment][column].stack->next;								//next is assigned the token uderneath the selected one
	free(board[row+row_increment][column].stack);													//memory is freed for old top of stack
	board[row+row_increment][column].stack = next;	

	//places token on chosen cell
	board[row][column].stack = push(temp, board[row][column].stack);				//square above selected gets new top token
	board[row][column].numTokens++;	

	//sorts out moving horizontally
	temp = board[row][column].stack->token;									//temp is assigned the top token of the selected square
	next = board[row][column].stack->next;								//next is assigned the token uderneath the selected one
	free(board[row][column].stack);													//memory is freed for old top of stack
	board[row][column].stack = next;

	//places counter on chosen cell	
	board[row][column+col_increment].stack = push(temp, board[row][column+col_increment].stack);				//square above selected gets new top token
	board[row][column+col_increment].numTokens++;
}
void move_right (square board[NUM_ROWS][NUM_COLUMNS], int roll) 
{
	int column=0;
	int row=roll;
	token * temp = board[row][column].stack->token;									//temp is assigned the top token of the selected square
	stack_token * next = board[row][column].stack->next;								//next is assigned the token uderneath the selected one
	free(board[row][column].stack);													//memory is freed for old top of stack
	board[row][column].stack = next;	
			
		//places token on chosen cell
	board[row][column+1].stack = push(temp, board[row][column+1].stack);				//square above selected gets new top token
	board[row][column+1].numTokens++;
}
/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    int i, j;
    for(i = 0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (j = 0; j < NUM_COLUMNS; j++){
        	//if the square (i,j) is empty
                //c is assigned 'X' if the square represents an obstacle
            if(board[i][j].type == OBSTACLE){
            	c = 'X';
			}
                  
                //c is assigned an empty space otherwise
               else{
                	if(board[i][j].stack != NULL){
                		c = print_token(board[i][j].stack->token);
					}
                		else c = ' ';
				} 
            
            
            
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
	int minNumOfTokens = 0;																		//the minimum number of tokens, if selected square has more tokens than this, selection is invalid
	int selectedSquare = 0;																		//user selected square

    int i, j;				//for loop increment variable
    int err;				//invalid input tracker
    	
    for(i=0;i<4;i++){						//loops through tokens
    	for(j=0;j<numPlayers; j++){			//loops through players
    		
    		printf("%s please select a square.\n", players[j].name);
			err = 1;	
			while(err != 0){
				printf("Enter row: ");
				scanf("%d", &selectedSquare);
				if (selectedSquare >= NUM_ROWS || selectedSquare < 0){							//if selected square is out of bounds an error message is printed
					printf("Square does not exist. Try again.\n");
				} 
					else if ((board[selectedSquare][0].numTokens) == minNumOfTokens){			//checks if the selected square has the smallest amount of tokens
						if(board[selectedSquare][0].stack == NULL)	err = 0;					//if the selected square is empty then the selection is valid	
							else if(board[selectedSquare][0].stack->token->col != (players[j].playercolor)) err = 0;	//if the selected square's top token is not the same color as the player's colour then the selection is valid
								else printf("Invalid input. Try again.\n"); 
					}	
						else printf("Invalid input. Try again.\n");

			}
			
			token * newtoken = (token *) malloc (sizeof(token));								//new token is created
			newtoken->col = players[j].playercolor;												//the new token's colour is assigned the player's colour
			board[selectedSquare][0].stack = push(newtoken, board[selectedSquare][0].stack);	//token is added to the top of the stack on the selected square
			
    		board[selectedSquare][0].numTokens++;												//number of tokens on selected square is incremented
			
    		/*TO BE IMPLEMENTED: if the square contains the minimum number of tokens
    		and does not have a token of the same color of the player */
    		//Checks each square of first column to see if stack is necessary
    		
    		//updates the minimum number of Tokens
    		if(((numPlayers * i) + j + 1)%NUM_ROWS == 0)
    			minNumOfTokens++;
		}
	}


}


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){

    srand(time(NULL));							// sets the seed for the random number function
	int dieRoll;
	int i;
	int x;
  for(i=0;i<numPlayers; i++){
  	printf("It's %s's turn!\n", players[i].name);
	dieRoll = (rand() % NUM_ROWS);
	printf("Number rolled: %d\n", dieRoll);
	printf("Would you like to move an adjacent token (1) or any token (2) sideways?\n");
	scanf("%d", &x);
	if(x == 1) move_adj(board, players, i, dieRoll);
		else if (x == 2) move_vertical(board, players, i);
	move_right(board, dieRoll);
	print_board(board);
=======
    srand(time(NULL));										// sets the seed for the random number function
	int dieRoll;											// number rolled
	int i, j;												//for loop increment variable
	int err;
	for(i=0;i<numPlayers; i++){
	printf("It's %s's turn!\n", players[i].name);
	err = 1;
	while(err != 0){										//rolls die until the row corresponding to the rolled number has atleast one token
		dieRoll = (rand() % (NUM_ROWS));					// die is rolled
		for(j = 0; j < NUM_COLUMNS; j++){
			if(board[dieRoll][j].stack != NULL) err=0;		//if atleast one square on the row that was rolled has a token, while loop ends
		}
	}	
	printf("Number rolled: %d\n", dieRoll);
	move_sideways(board, players, i);						//	function for selecting and moving a token up or down one space
//	move_horizontal(board, dieRoll);
	print_board(board);										// prints board at end of players turn
	}
	
	
}


void move_vertical (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum){
	int row, clm;																		//selected row
	char yesOrNo;																		//user input
	char * upOrDown;																	//user

void move_sideways (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum){
	int row, clm;																		//selected row
	int yesOrNo;																		//user input for yes or no
	char * upOrDown;																	//user input for up or down

	int err = 1;																		//invalid input tracker
	printf("Do you want to move a token up or down? Y/N\n");							//asks user for input
	while(err != 0){																	//loops until input is valid
		scanf("%s", &yesOrNo);															//reads input for yesOrNo
		if(yesOrNo == 'y' || yesOrNo == 'Y'){											//if input is y or Y then asks user to select a row
			printf("Which token would you like to move?\n");							//asks user for input

			while(err != 0){															//loops until input for row is valid
				printf("Enter row:");														
				scanf("%d", &row);														//reads input for row

				err == 1;																

				printf("Enter column:");														
				scanf("%d", &clm);
				if(row >= NUM_ROWS || row < 0 || clm >= NUM_COLUMNS || clm < 0){		//if selected row or column is greater or smaller than the number of rows or columns
					printf("Square does not exist. Try again.\n");						//prints error message

				}
					else if(board[row][clm].stack == NULL){								//checks if there is a token on the selected square
						printf("Empty square selected! Try again.\n");
					}	
						else if(board[row][clm].stack->token->col != players[playerNum].playercolor){		//prints error if selected token is not theirs
							printf("That's not your token! Try again.\n");																
						}
							else if(board[row][clm].stack->token->col == players[playerNum].playercolor){	//if the token is their own while loop ends
								err = 0;															
							}
								else {
									printf("Invalid input. Try again.\n");
								}
			}
			
			printf("Do you want to move it up or down? U/D\n");
  
			scanf("%c", &upOrDown);
			
			token * temp = board[row][0].stack->token;									//temp is assigned the top token of the selected square
			stack_token * next = board[row][0].stack->next;								//next is assigned the token uderneath the selected one
			free(board[row][0].stack);													//memory is freed for old top of stack
			board[row][0].stack = next;													//selected square gets assigned new top
			
			if(upOrDown == 'u' || upOrDown == 'U'){										//checks if user input u or U
				board[row-1][0].stack = push(temp, board[row-1][0].stack);				//square above selected gets new top token
				board[row-1][0].numTokens++;											//number of tokens on new square is incremented
				err = 0;																// no invalid input
			}
				else if (upOrDown == 'd' || upOrDown == 'D'){							//checks if user input d or D
					board[row+1][0].stack = push(temp, board[row+1][0].stack);			//square below selected square get new top token
					board[row+1][0].numTokens++;										//number of tokens on new square is incremented
					err = 0;															//no invalid input
				}		
					else {
						err = 1;
					}
					
			while(err != 0){
				printf("Invalid input. Try again.\n");
				scanf("%s", &upOrDown);
			
			printf("%d", board[row][0].stack->next->token->col);
			token * temp = board[row][0].stack->token;
			stack_token * next = board[row][0].stack->next;
			free(board[row][0].stack);
			board[row][0].stack = board[row][0].stack->next;
			
			if(upOrDown == 'u' || upOrDown == 'U'){
				board[row-1][0].stack = push(temp, board[row-1][0].stack);
				board[row-1][0].numTokens++;
				err = 0;
			}
				else if (upOrDown == 'd' || upOrDown == 'D'){
					board[row+1][0].numTokens++;
					board[row+1][0].stack = push(temp, board[row+1][0].stack);
					err = 0;

			err = 1;					//initializes invalid input tracker
			while(err != 0){	
				scanf("%s", &upOrDown);	//reads input for upOrDown
				
				if((row == 0 && (upOrDown == 'u' || upOrDown == 'U')) || row == 5 && (upOrDown == 'd' || upOrDown == 'D')){	//if token is at the top or bottom row it cannot be moved up or down respectively
					printf("Token cannot be moved in that direction. Try again.\n");

				}
					else if(upOrDown == 'u' || upOrDown == 'U'){								//checks if user input u or U
						token * temp = board[row][clm].stack->token;							//temp is assigned the top token of the selected square
						stack_token * next = board[row][clm].stack->next;						//next is assigned the token uderneath the selected one
						free(board[row][clm].stack);											//memory is freed for old top of stack
						board[row][clm].stack = next;											//selected square gets assigned new top
						board[row-1][clm].stack = push(temp, board[row-1][clm].stack);			//square above selected gets new top token
						board[row-1][clm].numTokens++;											//number of tokens on new square is incremented
						err = 0;																// no invalid input
					}
						else if (upOrDown == 'd' || upOrDown == 'D'){							//checks if user input d or D
							token * temp = board[row][clm].stack->token;						//temp is assigned the top token of the selected square
							stack_token * next = board[row][clm].stack->next;					//next is assigned the token uderneath the selected one
							free(board[row][clm].stack);										//memory is freed for old top of stack
							board[row][clm].stack = next;										//selected square gets assigned new top
							board[row+1][clm].stack = push(temp, board[row+1][clm].stack);		//square below selected square get new top token
							board[row+1][clm].numTokens++;										//number of tokens on new square is incremented
							err = 0;															//no invalid input
						}
							else {
								printf("Invalid input. Try again.\n");
							}
			}			
			board[row][clm].numTokens--;														//decreases number of tokens on selected square after a token has been moved
		}
		else if(yesOrNo == 'n' || yesOrNo == 'N') return;		//if user inputs n or N functions is quit
			else{
				printf("Invalid input. Try again.\n");
			}
	}
}

void move_adj (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum, int roll)
{
	char yesOrNo;
	char above_below;
	int column;
	int row=roll;
	printf("Enter the column in which you would like to have a counter moved");
	scanf("%d",&column);
	
	if (column>8)
	{
		printf("Error invalid input");
    }
	
	while(column<8)
	{
		if(board[1][column].stack || board[2][column].stack|| board[3][column].stack || board[4][column].stack)
		{
        	
			printf("Adjacent counter will be moved");
		
				if(board[row-1][column].stack->token->col == players[playerNum].playercolor)
				{
					//Goes through board to make sure no above adjacent option is given for squares in the first row 
					obstacle(square board[NUM_ROWS][NUM_COLUMNS],column);
					move_adjacent(board,-1,1, roll);	
				}
				
				else if(board[row+1][column].stack->token->col == players[playerNum].playercolor)
				{
					obstacle(square board[NUM_ROWS][NUM_COLUMNS],column);
					move_adjacent(board, 1, 1, roll);
				}
				
				else if(board[row-1][column].stack->token->col == players[playerNum].playercolor && board[row+1][column].stack->token->col == players[playerNum].playercolor)
				{
					printf("You have two adjacent tokens,to move the counter above enter 'a' to move the counter below enter 'b'");
					scanf("%c",above_below);
					if(above_below == 'a' || yesOrNo == 'A')
					{
						obstacle(square board[NUM_ROWS][NUM_COLUMNS],column);
						move_adjacent(board,-1,1, roll);
					}
					
					else if(above_below == 'b' || above_below == 'B')
					{
						obstacle(square board[NUM_ROWS][NUM_COLUMNS],column);
						move_adjacent(board,1,1,roll);
					}
				
				}
		}

		
		else if(row == 0)
		{
			if(board[row+1][column].stack->token->col == players[playerNum].playercolor)
			{
				printf("Do you want to move your adjacent counter, enter 'y' for yes and 'n' for no");
				scanf("%c", &yesOrNo);		//reads input for yesOrNo
				
				if(yesOrNo == 'y' || yesOrNo == 'Y')
				{
					obstacle(square board[NUM_ROWS][NUM_COLUMNS],column);
					move_adjacent(board, 1, 1, roll);
					
				}
				
			}
		}
		
		else if(row == 5)
		
			if(board[row-1][column].stack->token->col == players[playerNum].playercolor)
			{
				printf("Do you want to move your adjacent counter, enter 'y' for yes and 'n' for no");
				scanf("%c", &yesOrNo);		//reads input for yesOrNo
				
				if(yesOrNo == 'y' || yesOrNo == 'Y')
				{
					obstacle(square board[NUM_ROWS][NUM_COLUMNS],column);
					move_adjacent(board, -1, 1, roll);
					
				}
				else
				{
					break;
				}
			}
		}
	}


//void option2(square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum)
//{
//	int col;
//	printf("Enter the column you wish to have a counter move in");
//	scanf("%d",&column);
//	
//	if(column>8)
//	{
//		printf("Invalid input");
//	}
//	
//	while(column>8)
//	{
//		move_right(square board[NUM_ROWS][NUM_COLUMNS],1);
//		f
//	}
//}
//
void obstacle(square board[NUM_ROWS][NUM_COLUMNS], int curr_column)
{
 
	for(int i = 0; i< NUM_ROWS ; i++)
	{
		for(int j=0;curr_column-1;j++)
		{
		
			if(board[i][curr_column].stack != NULL)
			{
				printf("You are caught in an obstacle! You cannot move until all tokens to your left are gone:(");
				return;
			}
		}
	}
}

//void winner(square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum)
//{
//	for(int i = 0; i< NUM_ROWS ; i++)
//	{
//		if(board[i][8].stack == players[playerNum].playercolor)
//		{
//			players[playerNum].playerwinning++;
//			
//		}
//	}
//
//	
//}








