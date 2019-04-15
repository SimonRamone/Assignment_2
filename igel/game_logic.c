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
void move_horizontal (square board[NUM_ROWS][NUM_COLUMNS], int roll);

struct stack_token * push(token *newtoken, struct stack_token *top){
    struct stack_token *curr = top;
    top = malloc(sizeof(stack_token));
    top->token = newtoken;
    top->next = curr;
    return top;
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
    for(i =0; i < NUM_ROWS; i++){
       
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
	int minNumOfTokens = 0;
	int selectedSquare = 0;

    int i, j;
    int err;
    
    for(i=0;i<4;i++){
    	for(j=0;j<numPlayers; j++){	
    		
    		printf("%s please select a square.\n", players[j].name);
			err = 1;	
			while(err != 0){
				scanf("%d", &selectedSquare);
				if (selectedSquare >= NUM_ROWS || selectedSquare < 0){
					printf("Invalid input. Try again.\n");
				} 
					else if ((board[selectedSquare][0].numTokens) == minNumOfTokens){
						if(board[selectedSquare][0].stack == NULL)	err = 0;
							else if(board[selectedSquare][0].stack->token->col != (players[j].playercolor)) err = 0;
								else printf("Invalid input. Try again.\n"); 
					}	
						else printf("Invalid input. Try again.\n");

			}
			
			token * newtoken = (token *) malloc (sizeof(token));
			newtoken->col = players[j].playercolor;
			board[selectedSquare][0].stack = push(newtoken, board[selectedSquare][0].stack);
			
    		board[selectedSquare][0].numTokens++;
			
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
  for(i=0;i<numPlayers; i++){
  	printf("It's %s's turn!\n", players[i].name);
	dieRoll = 0+(rand() % NUM_ROWS);
	printf("Number rolled: %d\n", dieRoll);
	move_vertical(board, players, i);
	move_horizontal(board, dieRoll);
	print_board(board);
	}
	
	
}

void move_vertical (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum){
	int row, clm;																			//selected row
	int yesOrNo;																		//user input
	char * upOrDown;																		//user input
	int err = 1;																		//invalid input tracker
	printf("Do you want to move a token up or down? Y/N\n");							//asks user for input
	while(err != 0){																	//loops until input is valid
		scanf("%s", &yesOrNo);															//reads input for yesOrNo
		if(yesOrNo == 'y' || yesOrNo == 'Y'){											//if input is y or Y then asks user to select a row
			printf("Which token would you like to move?\n");							//asks user for input

			while(err != 0){															//loops until input for row is valid
				printf("Enter row:");														
				scanf("%d", &row);															//reads input for row
				printf("Enter column:");														
				scanf("%d", &clm);
				if(board[row][clm].stack == NULL && row < NUM_ROWS && row > -1 && clm < NUM_COLUMNS && clm > -1){
					printf("Empty square selected! Try again.\n");
				}	
					else if(row < NUM_ROWS && row > -1 && clm < NUM_COLUMNS && clm > -1 && board[row][clm].stack->token->col != players[playerNum].playercolor){	//prints error if selected token is not theirs
						printf("That's not your token! Try again.\n");																
					}
						else if(row < NUM_ROWS && row > -1 && clm < NUM_COLUMNS && clm > -1 && board[row][clm].stack->token->col == players[playerNum].playercolor && board[row][clm].stack != NULL){	//if the token is theirs
							err = 0;															//while loop ends
						}
							else {
								printf("Invalid input. Try again.\n");
							}
			}
			
			printf("Do you want to move it up or down? U/D\n");
			err = 1;
			while(err != 0){
				
			scanf("%s", &upOrDown);
			
			token * temp = board[row][clm].stack->token;									//temp is assigned the top token of the selected square
			stack_token * next = board[row][clm].stack->next;								//next is assigned the token uderneath the selected one
			free(board[row][clm].stack);													//memory is freed for old top of stack
			board[row][clm].stack = next;													//selected square gets assigned new top
			
			if(upOrDown == 'u' || upOrDown == 'U'){										//checks if user input u or U
				board[row-1][clm].stack = push(temp, board[row-1][clm].stack);				//square above selected gets new top token
				board[row-1][clm].numTokens++;											//number of tokens on new square is incremented
				err = 0;																// no invalid input
			}
				else if (upOrDown == 'd' || upOrDown == 'D'){							//checks if user input d or D
					board[row+1][clm].stack = push(temp, board[row+1][clm].stack);			//square below selected square get new top token
					board[row+1][clm].numTokens++;										//number of tokens on new square is incremented
					err = 0;															//no invalid input
				}
					else {
						printf("Invalid input. Try again.\n");
					}
			}
			
			board[row][clm].numTokens--;	
		}
		else if(yesOrNo == 'n' || yesOrNo == 'N') return;		//if user inputs n or N functions is quit
			else{
				printf("Invalid input. Try again.\n");
			}
	}
}

void move_horizontal (square board[NUM_ROWS][NUM_COLUMNS], int roll){
	
}





