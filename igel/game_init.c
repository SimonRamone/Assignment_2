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
                board[i][j].stack = NULL;									//!!!
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
               board[i][j].stack = NULL;		//!!!
                //board[i][j].stack->token->col = -1;
            }
            board[i][j].numTokens = 0;
            
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
    int j;
    int playerwinning=0;
    char *colors[6] = {"Red", "Blue", "Green", "Yellow", "Pink", "Orange"};
    int picked[6] = {0, 0, 0, 0, 0, 0};
    int i=0;
    printf("Insert player %d's name:\n", i+1);
    fgets(players[i].name,20,stdin);
    strtok(players[i].name, "\n");
    enum color pick =0;
    for(j=0;j<6;j++){
            if(picked[j] != 1)printf("%d. %s ", j+1, colors[j]);
        }
    printf("\n");
        scanf("%d", &pick);
      
        players[i].playercolor = --pick;
        getc(stdin);
        picked[players[i].playercolor]++;
        printf("\n");
        i++;
    while(i<6){
    	 printf("Insert player %d's name:\n", i+1);
       	fgets(players[i].name,20,stdin);
       	strtok(players[i].name, "\n");
        if(players[i].name[0] == '\n')
             break;
        for(j=0;j<6;j++){
            if(picked[j] != 1)printf("%d. %s ", j+1, colors[j]);
        }
        printf("\n");
        scanf("%d", &pick);
        players[i].playercolor = --pick;
        getc(stdin);
        picked[players[i].playercolor]++;
       printf("\n");
		//Checks whether a carriage return symbol was provided as input
        i++;
    }
    printf("\n");
return i;
}
