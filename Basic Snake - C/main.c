/**********************************
 * Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-110-03
 * Exercise 4
 *********************************/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    // Use pointers that point to the inputted parameters so that we can change their value in the Get_4_Numbers function.
    int width, height, snake, start;
    int *pHeight, *pWidth, *pSnake, *pStart;
    // The inputted string that contains the parameters will be max 100 characters. Add one more for the null character.
    char input[101];
    
    pHeight = &height;
    pWidth = &width;
    pSnake = &snake;
    pStart = &start;
    
    char move;
    int gameOver;
    int turn = 0;
    int *pTurn;
    pTurn = &turn;
    
    // The variable "good" tells us whether or not the input was good input. If it wasn't, print "Error" and end the program.
    int good = Get_4_Numbers(input, pWidth, pHeight, pSnake, pStart);
    // Get_4_Numbers returns 0 if there weren't at least 4 numbers in the inputted string.
    if (good == 0){
        printf("Error\n");
        return 0;
    }
    /*
     * If there were at least 4 numbers in the inputted string, we still have to check that none of the values are
     * too big, negative, etc. That's what the function Check_Input is for.
     */
    else if (good == 1)
        good = Check_Input (width, height, snake, start);
    
    if (good == 0)
        return 0;
    
    /*
     * The 2D array snakeCoords will store the coordinates of each piece of the snake. The snake can only be as long as 
     * as the perimeter of the rectangle, so the number of rows in the 2D array is equal to the perimeter of the rectangle.
     * And there are three columns. The first column stores the row coordinate, the second stores the column coordinate, 
     * and the third tells whether this piece will be a small x or a big X.
     */
	int snakeCoords_rows = 2 * width + 2 * height - 4;
	int** snakeCoords = malloc(snakeCoords_rows * sizeof(int*));
	if (snakeCoords == NULL) {
		printf("Error allocating memory");
		return 1;
	}
	for (int i = 0; i < snakeCoords_rows; i++) {
		snakeCoords[i] = malloc(3 * sizeof(int));
		if (snakeCoords[i] == NULL) {
			printf("Error allocating memory");
			return 1;
		}
	}

    // This function assigns values to the coordinates in snakeCoords according to the starting position of the snake.
    Start_Loc (snakeCoords, width, height, snake, start);
    // Now, print the board with the snake (and the turn number above it) using the current coordinates in snakeCoords.
    Print_Board (snakeCoords, width, height, snake, pTurn);
    
    // Infinite loop keeps the program running as long as the user doesn't enter an 'e' or make a move that ends the game.
    for ( ; ;){
        scanf_s(" %c", &move);
        
        if (move == 'E' || move == 'e'){
            return 0;
        }
        else {
            /*
             * Check if this move will end the game. If it does end the game, the Move function will not move the snake
             * and will return 1. If it does not end the game, the Move function will move the snake accordingly and return
             * 0.
             */
            gameOver = Move (snakeCoords, width, height, snake, move);
            // If this move ends the game...
            if (gameOver == 1){
                // Cue the end of game animation, and end the program.
                End_Game (snakeCoords, width, height, snake);
                return 0;
            }
            // If the move does not end the game...
            else if (gameOver == 0){
                // Print the board with the new location of the snake.
                Print_Board(snakeCoords, width, height, snake, pTurn);
            }
        }
    }
    
    return 0;
}
