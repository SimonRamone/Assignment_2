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
<<<<<<< HEAD
    int i, j,k;
=======
    int i, j;
    int err = 0;
    
>>>>>>> af468aebdf7bd481dd729a46fb0b1e0ca9a4fa7f
    for(i=0;i<4;i++){
    	for(j=0;j<numPlayers; j++){	
    		
    		printf("%s please select a square.\n", players[j].name, j+1);
    		scanf("%d", &selectedSquare);
    		//board[selectedSquare][0].stack = (token *) malloc (sizeof(token));
    		if (selectedSquare > 5 || selectedSquare < 0) err = 1;
				else if ((board[selectedSquare][0].numTokens) == minNumOfTokens){
					if(board[selectedSquare][0].stack == NULL)	err = 0;
						else if(board[selectedSquare][0].stack->token->col != (players[j].playercolor)) err = 0;
					else err = 1;
				}	
					else err = 1;
				
			while(err != 0){
				printf("Invalid input. Try again.\n");
				scanf("%d", &selectedSquare);
			//board[selectedSquare][0].stack = (token *) malloc (sizeof(token));
				if (selectedSquare > 5 || selectedSquare < 0) err = 1;
				else if ((board[selectedSquare][0].numTokens) == minNumOfTokens){
					if(board[selectedSquare][0].stack == NULL)	err = 0;
						else if(board[selectedSquare][0].stack->token->col != (players[j].playercolor)) err = 0;
					else err = 1;
				}	
					else err = 1;
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
	dieRoll = 0+(rand() % 5);
	printf("Number rolled: %d\n", dieRoll);
	move_vertical(board, players, i);
	move_horizontal(board, dieRoll);
	}
	
	
}

void move_vertical (square board[NUM_ROWS][NUM_COLUMNS], player players[], int playerNum){
	int row;
	int yesOrNo;
int upOrDown;
	int err = 1;
	printf("Do you want to move a token up or down? Y/N\n");
	while(err != 0){
		scanf("%s", &yesOrNo);
		if(yesOrNo == 'y' || yesOrNo == 'Y'){
			printf("Which token would you like to move?\n");
			printf("Enter row:");
			scanf("%d", &row);
			while(err != 0){
				if(board[row][0].stack->token->col != players[playerNum].playercolor){
				printf("That's not your token! Try again.\n");
				scanf("%d", &row);
				err == 1;
				}
					else if(board[row][0].stack->token->col == players[playerNum].playercolor){
						err = 0;
					}
						else {
							printf("Invalid input. Try again.\n");
							err = 1;
						}
			}
			
			printf("Do you want to move it up or down? U/D\n");
			scanf("%s", &upOrDown);
			
			printf("%d", board[row][0].stack->next->token->col);
			token * temp = board[row][0].stack->token;
			stack_token * next = board[row][0].stack->next;
			//free(board[row][0].stack);
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
				}
					else {
						err = 1;
					}
					
			while(err != 0){
				printf("Invalid input. Try again.\n");
				scanf("%s", &upOrDown);
				if(upOrDown == 'u'){
				board[row-1][0].numTokens++;
				board[row-1][0].stack->token->col = board[row][0].stack->token->col;
				err = 0;
			}
				else if (upOrDown == 'd'){
					board[row+1][0].numTokens++;
					board[row+1][0].stack->token->col = board[row][0].stack->token->col;
					err = 0;
				}
					else {
						err = 1;
					}
			}
			
			board[row][0].numTokens--;
			board[row][0].stack = NULL;		
		}
		else if(yesOrNo == 'n' || yesOrNo == 'N') return;
			else{
				err = 1;
				printf("Invalid input. Try again.\n");
			}
	}
	
	//print_board(board);
}

void move_horizontal (square board[NUM_ROWS][NUM_COLUMNS], int roll){
	
}





