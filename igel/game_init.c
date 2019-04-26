/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   int i, j;
    for (i =0; i< NUM_ROWS; i++){
        for(j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;									
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;				//sets stack of each square to empty
            board[i][j].numTokens = 0;				//initialises numTokens for each square
            
        }
    }
}
    
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){ 
    char *colors[6] = {"Red", "Blue", "Green", "Yellow", "Pink", "Orange"};		//for printing colour names
    int picked[6] = {0, 0, 0, 0, 0, 0};											//keeps track whether a colour has already been picked
    int i=0;																	//while loop increment variable (number of players)
    int j;																		//for loop increment variable
    int err;																	//keeps track of incomplete or invalid input
    int pick;																	//user selected colour
    while(i<6){
    	printf("Insert player %d's name:\n", i+1);
       	fgets(players[i].name,20,stdin);										//reads player name
       	strtok(players[i].name, "\n");											//remove newline symbol from end of player name
        if(players[i].name[0] == '\n')											//Checks whether a carriage return symbol was provided as input
             break;
        printf("Enter number to select token color:\n");
        for(j=0;j<6;j++){
            if(picked[j] != 1)printf("%d. %s ", j+1, colors[j]);				//prints all colours that haven't been selected
        }
        printf("\n");
        err = 1;
        while(err != 0){														//loops until selected colour is valid
        	scanf("%d", &pick);
        	getc(stdin);
        	if(pick > 6 || pick < 1){											//if input is greater or smaller than the number of colours, program asks for new input
        		printf("Invalid input. Try again.\n");
			}
	        	else if(picked[pick-1] == 1){									//if colour has been selected previously, program asks for new input
	        		printf("%s has already been picked. Choose a different color:\n", colors[pick-1]);
				}
					else if(picked[pick-1] != 1) err = 0;						//if colour hasn't been selected previously, while loop ends
						else printf("Invalid input. Try again.\n");				//prints erroor message if input is invalid
		}
        players[i].playercolor = --pick;										//selected colour is assigned to players colour
        picked[players[i].playercolor]++;										//marks colour as selected
       	printf("\n");

        i++;
    }
return i;																		//returns number of players
}
