///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      board1.txt board2.txt board3.txt board4.txt
// Semester:         CS 354 Spring 2020
//
// Author:           Zach Huemann
// Email:            zhuemann@wisc.edu
// CS Login:         huemann
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *COMMA = ",";  
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, COMMA);
    *size = atoi(token);
}       
 
   
  
/*
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {
    
    //checks for odd board length
    if ( (size%2) == 0) {
        return 0;
    }
    //checks number of Xs and Os to insure valid placement
    int numX = 0;
    int numO = 0;
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if ( *(*(board+i)+j) == 1) {
	        numX++;
	    }
    	    if ( *(*(board+i)+j) == 2) {
		numO++;
	    }		
	}
    }
    //checks to make sure there are as many or more X than O 
    if ( ((numX - numO) > 1) || ((numX - numO) < 0) )  {
	//printf("not corrct number of pieces.\n");
	return 0;
    }
    int numXwins = 0;
    int numOwins = 0;
    int match = 0;
    //checks for winning columns
    for (int j = 0; j < size-1; j++) {
	match = 0;
        for(int i = 0; i < size-1; i++) {
	    //if (board[i][j] == board[i+1][j]) {
	    if ( (*(*(board+i)+j)) == (*(*(board + i + 1)+j)) ) {
                match++;
	    }
	    if ( match == (size-1) ) {
	//	printf("found column winner");
                //if (board[i][j] == 1) {
		if ( *(*(board + i) + j) == 1 ) {
		    numXwins++;
		}
		//if (board[i][j] == 2) {
		if ( *(*(board + i) + j) == 2 ) {
		    numOwins++;
		}
	    }
         }
    }
    //checks for winning rows
    for (int i = 0; i < size-1; i++) {
	match = 0;
        for(int j = 0; j < size-1; j++) {
	    //if (board[i][j] == board[i][j+1]) {
	    if ( *(*(board+i)+j) == *(*(board+i)+j+1) ) {
                match++;
	    }
	    if (match == (size-1)) {
	//	printf("found row winner");
               // if (board[i][j] == 1) {
	        if ( *(*(board+i)+j) == 1) {
		    numXwins++;
		}
		//if (board[i][j] == 2) {
		if ( *(*(board+i)+j) == 2) {
		    numOwins++;
		}
	    }
         }
    }
    //if more than one player has a winning configuration
    //or a single player with moer than one win condition met
    //it is an invalid configuation
    if (numXwins + numOwins > 1) {
        return 0;
    }
/*
    //checks right diagonial
    match = 0;
    for (int i = 0; i < size-1; i++) {
	if (board[i][i] == board[i+1][i+1]) {
            match++;
	}
	if (match == (size-1)) {
	  //  printf("found right diaginal winner");
            if (board[i][i] == 1) {
		numXwins++;
	    }
	    if (board[i][i] == 2) {
                numOwins++;
	    }
	}    
    }
    //checks left diagional
    match = 0;
    for (int i = 0; i < size-1; i++) {
	if (board[i][size - i - 1] == board[i + 1][size - i - 1 - 1]) {
	    match++;
	}
	if (match == (size-1)) {
	   // printf("found left diaginal winner");
            if (board[i][size-i] == 1) {
		numXwins++;
	    }
	    if (board[i][size-i] == 2) {
                numOwins++;
	    }
	}    
    }
    //the number of Xwins or Owins will only be greater than zero at this point
    //if there is a diagonal win or valid configuration
    //if (numXwins > 0) {
    //    return 1;
    //}
    //if (numOwins > 0) {
    //    return 1;
    //}
    */

    //it actually is sufficent to just check for parellel wins and correct
    //number of peices, if you have a diagonal win it cannot be invalid so
    //long as the piece and odd board conditions are met. the double win
    //can be checked for but is not needed. 
    return 1;   
}    
  
 
   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
    
    //Check if number of command-line arguments is correct.
    if (argc != 2) {
        printf("You did not include the correct number of arguements.\n");
	exit(1);
    }
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;

    //Call get_dimensions to retrieve the board size.
    get_dimensions(fp,&size);
    //Dynamically allocate a 2D array of dimensions retrieved above.
    int **board = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        *(board+i) = (int *)malloc(size * sizeof(int));
    }
    //Read the file line by line.
    //Tokenize each line wrt comma to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }
        //printf("\n");
        token = strtok(line, COMMA);
        for (int j = 0; j < size; j++) {
            //Complete the line of code below
            //to initialize your 2D array.
            /* ADD ARRAY ACCESS CODE HERE */
	    *(*(board+i)+j) = atoi(token);
            token = strtok(NULL, COMMA);
	    //printf("%d", *(*(board+i)+j) );
        }
    }
    //printf("\n");
    //Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    int answer = n_in_a_row(board,size);

    if (answer == 1) {
	printf("valid");
    }
    if (answer == 0) {
        printf("invalid");
    }
        
    //Free all dynamically allocated memory.
    for (int i = 0; i < size; i++) {
        int *pointerToBeFreed = *(board+i);
        free(pointerToBeFreed);
    }
    free(board);    
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       
