/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>

void printLine();

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
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
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
    for(i=0;i<4;i++){
    	for(j=0;j<numPlayers; j++){
    		
    		printf("Player %d please select a square\n", j+1);
    		scanf("%d", &selectedSquare);
    		
    		if(board[selectedSquare][0].numTokens == minNumOfTokens && board[selectedSquare][0].stack != players[j].playercolor){
    			board[selectedSquare][0].stack = (token *) malloc (sizeof(token));
    			board[selectedSquare][0].stack->col = players[j].playercolor;
    			board[selectedSquare][0].numTokens++;
			}
    		/*TO BE IMPLEMENTED: if the square contains the minimum number of tokens
    		and does not have a token of the same color of the player */
    		
    		
    		
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
	int diceRoll;
	int input = 0;
	int col, row;
	int upOrDown;
	diceRoll = 1+(rand() % 6);
	printf("Number rolled: %d", diceRoll);
	printf("Do you want to move a token up or down? Enter 1 for yes.\n");
	scanf("%d", input);
	if(input == 1){
		printf("Which token would you like to move?\n");
		printf("Enter column:");
		scanf("%d", &col);
		printf("\n");
		printf("Enter row:");
		scanf("%d", &row);
		printf("\n");
		printf("Do you want to move it up or down? 1 or -1\n");
		scanf("%d", &upOrDown);
		board[row][col].numTokens--;
			
	}
	
	
}




