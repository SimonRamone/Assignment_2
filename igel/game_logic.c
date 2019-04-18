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

/*void move_horizontal (square board[NUM_ROWS][NUM_COLUMNS], int roll){
	int roll=0+rand()%6;
	int row = int column;
	
	char *upOrDown;
	int err = 1;
	printf("Do you want to mo a token up or down? Y/N\n");
	while(err != 0){
		scanf("%s", &yesOrNo);
		if(yesOrNo == 'y' || yesOrNo == 'Y'){
			printf("Which token would you like to move?\n");
			printf("Enter row:");
			scanf("%d", &row);
			while(err != 0){
	
	
}*/





