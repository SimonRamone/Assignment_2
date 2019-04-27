
// To change this license header, choose License Headers in Project Properties.
// To change this template file, choose Tools | Templates
// and open the template in the editor.



#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


void printLine(); 

void checkObstacle(square board[NUM_ROWS][NUM_COLUMNS]);													//changes obstacles to normal squares when there are no more tokens behind the obstacle
void move_sideways (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum);						//function for moving a token up or down
void move_adj(square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum, int roll);
void move_adjacent (square board[NUM_ROWS][NUM_COLUMNS], int row_increment, int col_increment, int roll);
void move_right (square board[NUM_ROWS][NUM_COLUMNS], int roll, int col);
bool canMove(square board[NUM_ROWS][NUM_COLUMNS], int curr_column);
bool isTokenInObstacle(square board[NUM_ROWS][NUM_COLUMNS], int curr_column);
bool isBoardBehindClear(square board[NUM_ROWS][NUM_COLUMNS], int curr_column);
bool countTokensInLastColumn(square board[NUM_ROWS][NUM_COLUMNS], player players[]);
struct stack_token * push(token *newtoken, struct stack_token *top);											//function for adding a token to the top of a stack

void move_adjacent (square board[NUM_ROWS][NUM_COLUMNS],int row_increment,int col_increment, int roll) {
	int column=0;
	int row= roll;
	if(board[row+row_increment][column].stack !=NULL){
		
		token * temp = board[row+row_increment][column].stack->token;									//temp is assigned the top token of the selected square
	
		board[row+row_increment][column].numTokens--;
		stack_token * next = board[row+row_increment][column].stack->next;								//next is assigned the token uderneath the selected one
		free(board[row+row_increment][column].stack);													//memory is freed for old top of stack
		board[row+row_increment][column].stack = next;	
		
			if(	board[row][column].stack != NULL){
			//places token on chosen cell
		board[row][column].stack = push(temp, board[row][column].stack);				//square above selected gets new top token
		board[row][column].numTokens++;	
			//sorts out moving horizontally
	temp = board[row][column].stack->token;									//temp is assigned the top token of the selected square
	next = board[row][column].stack->next;								//next is assigned the token uderneath the selected one
	free(board[row][column].stack);													//memory is freed for old top of stack
	board[row][column].stack = next;

	}
	
	
	if(board[row][column+col_increment].stack !=NULL){
			//places counter on chosen cell	
	board[row][column+col_increment].stack = push(temp, board[row][column+col_increment].stack);				//square above selected gets new top token
	board[row][column+col_increment].numTokens++;
	}

	}

}

void move_right (square board[NUM_ROWS][NUM_COLUMNS], int roll, int col) 
{	
	int column=col;
	int row=roll;
	token * temp = board[row][column].stack->token;									//temp is assigned the top token of the selected square
	board[row][column].numTokens--;
	stack_token * next = board[row][column].stack->next;								//next is assigned the token uderneath the selected one
	free(board[row][column].stack);													//memory is freed for old top of stack
	board[row][column].stack = next;	
			
		//places token on chosen cell
	board[row][column+1].stack = push(temp, board[row][column+1].stack);				//square above selected gets new top token
	board[row][column+1].numTokens++;
}

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
            if(board[i][j].type == OBSTACLE && board[i][j].stack != NULL){
            	c = print_token(board[i][j].stack->token);
			}
			else if(board[i][j].type == OBSTACLE){
            	c = 'X';
			}
                  
                //c is assigned an empty space otherwise
               else{
                	if(board[i][j].stack != NULL){
                		c = print_token(board[i][j].stack->token);
					}
                		else c = ' ';
				} 
            
            
            if(board[i][j].type == OBSTACLE && board[i][j].stack != NULL){
            	printf("| %c!", c);											//prints ! after token color letter to indicate that the token is on an obstacle square
			}
            	else printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
    printf("\n");
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
	char *colors[6] = {"Red", "Blue", "Green", "Yellow", "Pink", "Orange"};

    int i, j;				//for loop increment variable
    int err;				//invalid input tracker
    	
    for(i=0;i<4;i++){						//loops through tokens
    	for(j=0;j<numPlayers; j++){			//loops through players
    		
    		printf("%s [%s] please select a square.\n", players[j].name, colors[players[j].playercolor]);
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
			
    		
    		//updates the minimum number of Tokens
    		if(((numPlayers * i) + j + 1)%NUM_ROWS == 0)
    			minNumOfTokens++;
		}
	}
	printf("\n");
}


/*
 * Roll dice, move token sideways, move token right, check for winners
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

bool play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    srand(time(NULL));							// sets the seed for the random number function
    bool done = false;
	int dieRoll;
	int col;                                    //user selected column
	char *colors[6] = {"Red", "Blue", "Green", "Yellow", "Pink", "Orange"};			//color array for printing the players color
	int i, j;																			//for loop increment variable
	int x;																			//input for which sideways function the player wants to use
	int err;
  	for(i=0;i<numPlayers && !done; i++){											//loops through the players
  		printf("It's %s's [%s] turn!\n", players[i].name, colors[players[i].playercolor]);		//prints the players name and color when its their turn
  		err = 1;
		while(err != 0){										//rolls die until the row corresponding to the rolled number has atleast one token
			dieRoll = (rand() % (NUM_ROWS));					//die is rolled
			for(j = 0; j < NUM_COLUMNS; j++){
				if(board[dieRoll][j].stack != NULL) err=0;		//if atleast one square on the row that was rolled has a token, while loop ends
			}
		}
		printf("Number rolled: %d\n", dieRoll);
		printf("Would you like to move any token (1) or an adjacent token (2) sideways?\n");	//lets player which move sideways function they want to use Simonas's or Anu's
		scanf("%d", &x);
		if(x == 1) {
			move_sideways(board, players, i);													//Simonas's function for moving a token up or down
			print_board(board);
			col = 0;																			//col is initialised
			err = 1;																			
			for(j = 0; j < NUM_COLUMNS; j++){
				if(board[dieRoll][j].stack != NULL && j != NUM_COLUMNS-1 && board[dieRoll][j].type != OBSTACLE) err=0;		//checks if there is still atleast one movable token on the rolled row
			}
			if(err == 0){
				err = 1;
				while(err != 0){
					printf("Which token would you like to move forward in row %d?\n", dieRoll);
					printf("Enter column:");
					scanf("%d", &col);
					if(board[dieRoll][col].type != OBSTACLE){
						move_right(board, dieRoll,col);						//function for moving the token in the selected column and rolled row one square forward
						err = 0;
					}
						else printf("Invalid token selected. Try again.\n");
				}
				
			}
				else if (err > 0) printf("There are no tokens that can be moved forward in row %d. Skipping turn.\n", dieRoll);												
		}
		else if (x == 2){
			move_adj(board, players, i, dieRoll);												//Anu's function for moving a token up or down
		}
		printf("\n");
		checkObstacle(board);
		print_board(board);
		done = countTokensInLastColumn(board, players);											//keeps track of each players tokens in last column and prints winner		
 	}
 	
 	return done;
}

void move_sideways (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum){
	int row, clm;																		//selected row
	char yesOrNo;																		//user input for yes or no
	char upOrDown;																	//user input for up or down
	int err = 1;																		//invalid input tracker
	printf("Do you want to move a token up or down? Y/N\n");							//asks user for input
	while(err != 0){																	//loops until input is valid
		scanf("%s", &yesOrNo);															//reads input for yesOrNo
		if(yesOrNo == 'y' || yesOrNo == 'Y'){											//if input is y or Y then asks user to select a row
			printf("Which token would you like to move?\n");							//asks user for input

			while(err != 0){															//loops until input for row is valid
				printf("Enter row:");														
				scanf("%d", &row);														//reads input for row
				printf("Enter column:");														
				scanf("%d", &clm);
				if(row >= NUM_ROWS || row < 0 || clm >= NUM_COLUMNS || clm < 0){		//if selected row or column is greater or smaller than the number of rows or columns
					printf("Square does not exist. Try again.\n");						//prints error message
				}
					else if(board[row][clm].stack == NULL){								//checks if there is a token on the selected square
						printf("Empty square selected! Try again.\n");
					}
						else if(board[row][clm].type == OBSTACLE){
							printf("You have selected a token on an obstacle! Try again.\n");	//prints error if selected token is on an obstacle square
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
	
	if(column<9)
	{
		if(row==1 || row==2||row==3 || row==4)
		{
        	
		
			if(board[row-1][column].stack->token->col == players[playerNum].playercolor)
			{
				//Goes through board to make sure no above adjacent option is given for squares in the first row 
				  //Obstacle function is being called 
				  
				if(canMove(board,column)){
					move_adjacent(board,-1,1, roll);
					printf("Adjacent counter moved");	
				}	
			}
				
			else if(board[row+1][column].stack->token->col == players[playerNum].playercolor)
			{
				if(canMove(board,column)){  //Obstacle function is being called 
				move_adjacent(board, 1, 1, roll);
				printf("Adjacent counter moved");
				}
			}
				
			else if(board[row-1][column].stack->token->col == players[playerNum].playercolor && board[row+1][column].stack->token->col == players[playerNum].playercolor)
			{
				printf("You have two adjacent tokens,to move the counter above enter 'a' to move the counter below enter 'b'");
				scanf("%c",above_below);
				if(above_below == 'a' || yesOrNo == 'A')
				{
					if(canMove(board,column)){  //Obstacle function is being called 
					move_adjacent(board,-1,1, roll);
					printf("Adjacent counter moved");
				    }
				}
					
				else if(above_below == 'b' || above_below == 'B')
				{
					if(canMove(board,column)){//Obstacle function is being called 
					move_adjacent(board,1,1,roll);
					printf("Adjacent counter moved");
				   }
				}
				
			}
		}

		
		else if(row == 0)
		{
			if(board[row+1][column].stack->token->col == players[playerNum].playercolor)
			{
				if(canMove(board,column)){  //Obstacle function is being called 
				move_adjacent(board, 1, 1, roll);
				printf("Adjacent counter moved");
				}
			}
		}
		
		else if(row == 5)
		
			if(board[row-1][column].stack->token->col == players[playerNum].playercolor)
			{
				
				if(canMove(board,column)){  //Obstacle function is being called 
				move_adjacent(board, -1, 1, roll);
				printf("Adjacent counter moved");
				}
			}
		}
		printf("finishes this\n");
	}



bool isBoardBehindClear(square board[NUM_ROWS][NUM_COLUMNS], int curr_column)
{
 	int i, j;
	for(i = 0; i< NUM_ROWS ; i++)
	{
		for(j=0;j<curr_column-1;j++)
		{
		
			if(board[i][j].stack != NULL)
			{
				printf("Board behind not clear");
				return false;
			}
		}
	}
	
	return true;
}

bool isTokenInObstacle(square board[NUM_ROWS][NUM_COLUMNS], int curr_column) 
{
	return board[NUM_ROWS][NUM_COLUMNS].type == OBSTACLE;
}

bool canMove(square board[NUM_ROWS][NUM_COLUMNS], int curr_column) 
{
	if (isTokenInObstacle(board, curr_column) == false)
	{
		return true;
	} 
	else 
	{
		return isBoardBehindClear(board, curr_column);
	}
}




bool countTokensInLastColumn(square board[NUM_ROWS][NUM_COLUMNS], player players[])
{
	int redcounter=0,bluecounter=0,greencounter=0,yellowcounter=0,pinkcounter=0,orangecounter=0;
	struct stack_token *curr;
	bool finished = false;
	int i;
	for(i = 0; i< NUM_ROWS && !finished; i++)
	{
		if(board[i][8].stack != NULL)
		{
			curr=board[i][8].stack;
			while(!finished)
			{
				if(curr->token->col==RED)
				{
					redcounter++;
					if(redcounter==3){
						finished = true;
						printf("Red player wins\n");
					}
				}
				
				else if(curr->token->col==BLU)
				{
					bluecounter++;
					if(bluecounter==3){					
						finished = true;
						printf("Blue player wins\n");
					}
				}
				
				else if(curr->token->col==GREEN)
				{
					greencounter++;
					if(greencounter==3){
					
						finished = true;
						printf("Green player wins\n");
					}
				}
				
				else if(curr->token->col==YELLOW)
				{
					yellowcounter++;
					if(yellowcounter==3){
						finished = true;
						printf("Yellow player wins\n");
					}
						
				}
				
				else if(curr->token->col==PINK)
				{
					pinkcounter++;
					if(pinkcounter==3){
						finished = true;
						printf("Pink player wins\n");
					}
						
				}
				
				else if(curr->token->col==ORANGE)
				{
					orangecounter++;
					if(orangecounter==3){
						finished = true;
						printf("Orange player wins\n");
					}
				}
			}
				
		
		}
		
	}
	
	return finished;	
}

//changes obstacles to normal squares when there are no more tokens behind the obstacle
void checkObstacle(square board[NUM_ROWS][NUM_COLUMNS]){
	int i, j;						//for loop increment variables used for iterating through all the squares
	int m, n;						//for loop increment variables used for iterating through all the squares behind a column with an obstacle
	int numTokens;					//number of squares with atleast one token behind a column with an obstacle
	for(i = 0; i< NUM_ROWS ; i++){
		for(j=0;j<NUM_COLUMNS;j++){
			if(board[i][j].type == OBSTACLE){			//if a obstacle square is found, function loops through all the squares behind that column and counts squares that are not free
				numTokens = 0;							//initializes numTokens
				for(m = 0; m< NUM_ROWS; m++){			//loops trhough all rows	
					for(n=0;n< j;	n++){				//loops through columns up to but not including the column with the obstacle
						if(board[m][n].stack != NULL) numTokens++;		//keeps track of number of squares with atleast one token
					}
				}
				if(numTokens == 0) board[i][j].type = NORMAL;			//if there are no tokens behind a column with an obstacle square, the square becomes normal
			}
		}
	}
}


