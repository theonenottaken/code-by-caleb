/**********************************
 * Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-110-03
 * Exercise 4
 *********************************/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/*****************************************************************************************************
 * Function name: Get_4_Numbers
 * The input: A string, and four int pointers.
 * The output: The function returns 1 if it finds four whole numbers in the string, returns 0
 *             if there are less than four whole numbers in the string.
 * The Function operation: The function puts the inputted string into the array that was passed
 *                         as an argument. It then splits up the string by commas and makes a two-
 *                         dimensional array made up of substrings, where each substring is what is
 *                         in between the commas in the original inputted string. The function then
 *                         checks each substring. If it is only made up of numbers, then it calculates
 *                         the number and assigns its value to the address of the appropriate pointer.
 *****************************************************************************************************/
int Get_4_Numbers (char str[], int* a, int* b, int* c, int* d){
    int size = 0;
    char next;
    /*
     * Scan in the string that will include the parameters. Breaks when the user presses 'enter.' 
     * The use of the variable "next" prevents the line feed (ASCII value 10) from being included
     * at the end of the string. Each character is assigned at address "size" to be an element of 
     * the array that was passed as an argument to the function. After all the characters have been
     * scanned, assign the null value to the next element in the array - str[size].
     */
    for ( ; ; ){
        scanf_s("%c", &next);
        if (next == 10)
            break;
        else
            str[size] = next;
        size++;
    }
    str[size] = 0;
    
    /* 
     * Now, we go through the entire array that contains the inputted string and count how many
     * commas it contains, and also find the size of the largest substring in the array. Think of
     * the string as a set of substrings that are each separated by a comma. The variable "length"
     * keeps track of the size of each substring, and maxLength will be the value of length that was 
     * the highest after going through the entire string.
     */
    int j;
    int commas = 0;
    int length = 0;
    int maxLength = 0;
    for (j = 0; j < size; j++){
        if (str[j] != ','){
            length++;
            if (length > maxLength)
                maxLength = length;
        }
        if (str[j] == ','){
            commas++;
            length = 0;
        }
    }
    /*
     * Now, we make a two-dimensional array and assign values to it from the array str, which contains
     * the original inputted string. If there are x number of commas in the string, then there will always
     * be at least x + 1 substrings. So the number of rows in the 2D array is commas + 1. Then for the
     * number of columns, we use the value of maxLength and add one to make room for the null character at
     * the end of the largest substring. "i" counts through the rows of the matrix, "j" counts through the
     * columns, and strCount keeps track of which character from the original inputted string we're analyzing
     * at the moment. In the inner for loop, we keep looping as long as j is less than or EQUAL to maxLength
     * (not just less than) in order to not skip over the commas. If we skip over the commas, then strCount
     * will not be the correct index for the characters we want to look at. But the commas are not saved into
     * the 2D array. In addition, after finishing each row, we assign the null value to the next spot in that
     * row - matr[i][j].
     */
	char** matr = malloc((commas + 1) * sizeof(char*));
	if (matr == NULL) {
		printf("Error allocating memory");
		exit(1);
	}
	for (int i = 0; i < commas + 1; i++) {
		matr[i] = malloc((maxLength + 1) * sizeof(char));
		if (matr[i] == NULL) {
			printf("error allocating memory");
			exit(1);
		}
	}

    int strCount = 0;
    int i;
    for (i = 0; i < commas + 1; i++){
        for (j = 0; j <= maxLength; j++){
            // If we've reached a comma or the end of the string...
            if ((str[strCount] == ',') || (str[strCount] == 0)){
                strCount++;
                break;
            }
            else
                matr[i][j] = str[strCount];
            strCount++;
        }
        matr[i][j] = 0;
            
    }
    /*
     * Define a new variable type called bool because we have two important boolean values that we
     * have to consider. "number" will tell us if the substring is a number (that is, every character 
     * in the substring except perhaps a negative sign in the beginning is a number). And "negative"
     * will tell us if the number is negative. "whichVar" will keep track of which variable to assign
     * the value to (the first found number will get assigned to the first int in the argumets - int a.
     * The second will get assigned to int b, and so on.) "value" will be the value of the number, after
     * the computer makes sure that it is ideed a number. "length" will once again keep track of the
     * length of each substring. power, tenPower, and k will be used to calculate the value of a number.
     */
    typedef int bool;
    bool number = 1, negative = 0;
    int whichVar = 0;
    int value = 0;
    length = 0;
    int power = 0, tenPower = 1;
    int k;
    // The outer loop loops through the rows of the matrix.
    for (i = 0; i < commas + 1; i++){
        // If whichVar equals 4, that means we've already found four numbers. So break.
        if (whichVar == 4){
            break;
         }
        /*
         * This first inner loop just checks if the substring is a number, how long it is,
         * and if there's a negative sign at the beginning.
         */
        for (j = 0; j < maxLength; j++){
            // If the first character is a negative sign, roger that and move on to the next character.
            if ((j == 0) && (matr[i][j] == '-')){
                negative = 1;
                length++;
                continue;
            }
            /*
             * If just one character (after the first one) is not a digit from 0 to 9, then it's not a number
             * and move onto the next row in the matrix. A negative sign in the beginning will not get to this
             * point in the loop because of the keyword "continue" above. Also, if you reach the null character,
             * that doesn't mean the substring isn't a number. That just means you've reached the end of the substring.
             */
            if ((matr[i][j] < 48 || matr[i][j] > 57) && (matr[i][j] != 0)){
                number = 0;
                break;
            }
            // If you reach the end of the substring, stop looping through this substring.
            if (matr[i][j] == 0)
                break;
            /*
             * If we get to this point in the loop, that means the current character in the substring
             * is a number. So add one to length!
             */
            length++;
        }
        /*
         * If every character was a number and there was at least one character in the substring...
         * (It's possible that a row in the matrix could have no characters in it if the user inputted
         * two or more commas in a row.)
         */
        if (number == 1 && length > 0){
            whichVar++;
            /*
             * Start at the last digit because, in a number, the ones place is all the way on the right.
             * And if the number is negative, then "negative" will equal one, so only go until j is greater
             * than or equal to 0 + negative (the first character if there was no negative sign, the second
             * character if there was a negative sign).
             */
            for (j = length - 1; j >= 0 + negative; j--){
                /*
                 * If we're in the ones spot (the first iteration through this loop), then power equals
                 * zero, and tenPower remains at one. If we're in the tens spot (the second iteration through
                 * the loop, then tenPower will equal ten. If we're in the hundreds spot, tenPower equals 100, etc.
                 */
                for (k = 1; k <= power; k++){
                    tenPower *= 10;
                }
                /*
                 * Is everyone with me here? For example, if the number is 123, we're calculating the number by
                 * doing the following: 123 = 3 * 10^0 + 2 * 10^1 + 1 * 10^2. The ASCII value of a digit is always
                 * 48 more than its integer value, so we subtract 48 from the character in question to get the integer
                 * value. Then multiply it by tenPower, and add it to value.
                 */
                value += (matr[i][j] - 48) * tenPower;
                power++;
                tenPower = 1;
            }
            // If there was a negative sign at the beginning, multiply value by negative one.
            if (negative == 1)
                value *= -1;
            // If this the first number that we've found...
            if (whichVar == 1)
                *a = value;
            // If it's the second number...
            else if (whichVar == 2)
                *b = value;
            // Third...
            else if (whichVar == 3)
                *c = value;
            // Fourth...
            else if (whichVar == 4)
                *d = value;
        }
        // Reset anything that needs to be reset.
        value = 0;
        length = 0;
        power = 0;
        number = 1;
        negative = 0;
    }
    // If there were at least four numbers in the string, return 1.
    if (whichVar == 4)
        return 1;
    // Otherwise, return 0.
    return 0;    
}

/*******************************************************************************************************
 * Function name: Check_Input
 * The input: four integers
 * The output: The function returns 1 if all four integers are good inputs. Otherwise, it returns 0.
 * The Function operation: Just a bunch of if statements. First check if the width or height is less
 *                         than 2 or greater than 20. Then check if the snake is longer than the
 *                         the perimeter of the rectangle. Then check if the starting point is greater
 *                         than or equal to the perimeter (a is the width, b is height, c is length of
 *                         snake, and d is starting point). Then check if any of the values are negative.
 *******************************************************************************************************/
int Check_Input (int a, int b, int c, int d){
    if (a < 2 || a > 20){
        printf("Error\n");
        return 0;
    }
    if (b < 2 || b > 20){
        printf("Error\n");
        return 0;
    }
    // The perimeter of the rectangele is equal to twice the width plus twice the height, minus the four corners.
    if (c > ((2 * a) + (2 * b) - 4)){
        printf("Error\n");
        return 0;
    }
    if (d >= ((2 * a) + (2 * b) - 4)){
        printf("Error\n");
        return 0;
    }
    // No need to check for a and b, because we already made sure that they are greater than 2.
    if (c < 0 || d < 0){
        printf("Error\n");
        return 0;
    }
    return 1;
}

/*******************************************************************************************************
 * Function name: Start_Loc
 * The input: A 2D matrix that will contain the coordinates for the location of the snake, and four
 *            integer values: 1. the width of the rectangle, 2. the height of the rectangle, 3. the
 *            length of the snake, and 4. the starting point of the snake.
 * The output: The function doesn't return anything. But it does assign location coordinates to the
 *             elements of the 2D array. And it assigns a big X or little x to each piece of the snake.
 * The Function operation: This function is only concerned with the starting position of the snake, and
 *                         the snake has to start on the perimeter of the rectangle, so the function just 
 *                         looks at each side of the rectangle separately. 0 to width - 1 is the top side,
 *                         width - 1 to (width + height - 2) is the right side, and so on.
 *******************************************************************************************************/
void Start_Loc (int** matr, int w, int h, int sn, int st){
    /*
     * The variable loc will keep track of where along the perimeter of the rectangle we need to place the
     * next piece of the snake. We'll start from the very back of the snake and move towards the head. The 
     * rear of the snake will be placed on the starting point that was inputted as a parameter, so we initialize
     * loc to equal st. smallX will keep track of whether the current piece of the snake should be drawn with a
     * small x or a big X.
     */
    int loc = st;
    int i;
    typedef int bool;
    bool smallX = 1;
    
    for (i = 0; i < sn; i++){
        /*
         * Although the starting point cannot be greater than or equal to the perimeter of the rectangle, the
         * starting point could be just a little bit less than the perimeter and then the snake might have to
         * loop back around to the first row. Therefore, if loc ever gets to equal the perimeter of the rectangle,
         * make loc equal to 0 (the top left corner of the rectangle) and continue as normal.
         */
        if (loc == (2 * w) + (2 * h) - 4)
            loc = 0;
        // If loc is on the first row...
        if (loc <= w - 1){
            // The "row" coordinate of this piece in the snake is 0 (the first row)...
            matr[i][0] = 0;
            // ...and the "column" coordinate is loc.
            matr[i][1] = loc;
        }
        // If loc is on the right side of the rectangle (the last column)...
        else if ((w - 1) < loc && loc <= (w + h - 2)){
            matr[i][0] = loc - (w - 1);
            matr[i][1] = w - 1;
        }
        // If loc is on the bottom of the rectangle (the last row)...
        else if ((w + h - 2) < loc && loc <= (2 * w) + h - 3){
            matr[i][0] = h - 1;
            matr[i][1] = (2 * w) + h - 3 - loc;
        }
        // If loc is on the left side of the rectangle (the first column)...
        else if ((2 * w) + h - 3 < loc && loc < (2 * w) + (2 * h) - 4){
            matr[i][0] = (2 * w) + (2 * h) - 4 - loc;
            matr[i][1] = 0;
        }
        // Increment loc after plotting each piece.
        loc++;
    }
    // The head of the snake is actually going to be the last "row" in the 2D array, so start at sn - 1.
    for (i = sn - 1; i >= 0; i--){
        // If this piece requires a small x...
        if (smallX == 1)
            /*
             * It will become clear why I did this when we get to the Print_Board function. For now, just
             * remember that the ASCII value of 'x' is 120, and the ASCII value of 'X' is 88. So the difference
             * between those two is 32.
             */
            matr[i][2] = 32;
        else
            matr[i][2] = 0;
        /* By multiplying smallX by -1 after every iteration through the loop, we get the alternating effect that
         * we're looking for. For each piece of the snake, smallX will switch from 1 to -1 to 1 to -1...etc.
         */
        smallX *= -1;
    }
}

/***********************************************************************************************************
 * Function name: Print_Board
 * The input: A 2D matrix that contains the coordiates of the snake, an int that stores the width of the
 *            rectangle, an int for the height, an int for the length of the snake, and an int pointer that
 *            points to an int that tells us which turn in the game we're on right now.
 * The output: The function is void, but it does print the board for the current turn in the game.
 * The function operation: The function has one loop to go through the rows of the rectangle, another loop
 *                         inside of that one to go through the columns in each row, and another loop inside
 *                         of that one to go through each piece of the snake and check if a snake piece needs
 *                         to be printed in the current spot on the board. If a snake piece does not need to 
 *                         be printed, the function prints '-', '|', or '.' according to where on the board we're
 *                         printing at the moment.
 ***********************************************************************************************************/
void Print_Board (int** matr, int w, int h, int sn, int* t){
    // First, print which turn number this is. And then increment the turn number.
    printf("%d\n", *t);
    *t = *t + 1;
    /* 
     * i, j, and k are our counters. snakePiece is a boolean that tells whether or not we should print a snake
     * piece at the given spot on the board right now.
     */
    int i, j, k;
    int snakePiece = 0;
    
    for (i = 0; i < h; i++){
        for (j = 0; j < w; j++){
            for (k = 0; k < sn; k++){
                // If the coordinates of where we are on the board right now match the coordinates of a snake piece...
                if (matr[k][0] == i && matr[k][1] == j){
                    /*
                     * Print either a small x or a big X, depending on what is in the third column of the snake piece 
                     * in question. Remember from the function Start_Loc that if this piece needs to be a small x, the
                     * number in third column of the matrix will be 32. And if this piece needs to be a big X, the 
                     * number in the third column of the matrix will be 0. So 'X' + matr[k][2] will be 'X' if matr[k][2]
                     * equals 0, and it will be 'X' + 32 (which is 120, or 'x') if matr[k][2] equals 32.
                     */
                    printf("%c", 'X' + matr[k][2]);
                    snakePiece = 1;
                    // There will never be two pieces in the same spot so once you've found one, stop searching.
                    break;
                }
            }
            // If you've already printed a snake piece, move on to the next spot on the board.
            if (snakePiece == 1){
                snakePiece = 0;
                continue;
            }
            // If we're in the first row or the last row...
            if ((i == 0) || (i == h - 1))
                printf("-");
            // If we're not in the first or last row, but we are in the first or last column...
            else if ((j == 0) || (j == w - 1))
                printf("|");
            // If we're not in the first row, last row, first column, or last column...
            else
                printf(".");
        }
        // New line after each row.
        printf("\n");
    }
}

/******************************************************************************************************************
 * Function name: Move
 * The input: A 2D matrix that contains the coordinates of the snake, the width of the rectangle, the height of the
 *            rectangle, the length of the snake, and the inputted character that represents which direction the user
 *            wants to move the snake.
 * The output: The function changes the coordinates of the snake in the 2D array. It also returns an int that tells
 *             if this current move will end the game or not. 1 means that this move ends the game. 0 means that this
 *             move does not end the game.
 * The function operation: The function first finds the new coordinates of the head piece of the snake, based on the
 *                         move inputted by the user. But before changing the coordinates in the 2D array, it assigns
 *                         the new head coordinates to the variables check1 and check2, because we want to make sure
 *                         the move will not end the game before changing any of the coordinates in the 2D array. If 
 *                         this move ends the game, return 1 before changing any of the array elements. If not,
 *                         change each pair of coordinates in the array to the value of the coordinates of the piece
 *                         in front of that piece, and change the coordinates of the head piece to check1 and check2.
 *****************************************************************************************************************/
int Move (int** matr, int w, int h, int sn, char m){
    // check1 will represent the new row of the head piece. check2 will represent the new column of the head piece.
    int check1 = -1, check2 = -1;
    int i;
    
    if (m == 'u' || m == 'U'){
        // If the second piece of the snake is directly above the first piece...
        if (matr[sn - 1][0] - 1 == matr[sn - 2][0] && matr[sn - 1][1] == matr[sn - 2][1])
            // Move down instead of up.
            check1 = matr[sn - 1][0] + 1;
        else
            // Otherwise, move up.
            check1 = matr[sn - 1][0] - 1;
        // Column coordinate remains the same.
        check2 = matr[sn - 1][1];
    }
    else if (m == 'd' || m == 'D'){
        // If the second piece of the snake is directly below the first piece...
        if (matr[sn - 1][0] + 1 == matr[sn - 2][0] && matr[sn - 1][1] == matr[sn - 2][1])
            // Move up instead of down.
            check1 = matr[sn - 1][0] - 1;
        else
            // Otherwise, move down.
            check1 = matr[sn - 1][0] + 1;
        // Column coordinate remains the same.
        check2 = matr[sn - 1][1];
    }
    else if (m == 'r' || m == 'R'){
        // If the second piece is directly to the right of the first piece...
        if (matr[sn - 1][0] == matr[sn - 2][0] && matr[sn - 1][1] + 1 == matr[sn - 2][1])
            // Move left instead of right.
            check2 = matr[sn - 1][1] - 1;
        else
            // Otherwise, move right.
            check2 = matr[sn - 1][1] + 1;
        // Row coordinate remains the same.
        check1 = matr[sn - 1][0];
    }
    else if (m == 'l' || m == 'L'){
        // If the second piece is directly to the left of the first piece...
        if (matr[sn - 1][0] == matr[sn - 2][0] && matr[sn - 1][1] - 1 == matr[sn - 2][1])
            // Move right instead of left.
            check2 = matr[sn - 1][1] + 1;
        else
            // Otherwise, move left.
            check2 = matr[sn - 1][1] - 1;
        // Row coordinate remains the same.
        check1 = matr[sn - 1][0];
    }
    // If the coordinates check1 and check2 would mean that the head piece is now off the board...
    if (check1 > h - 1 || check1 < 0 || check2 > w - 1 || check2 < 0)
        // Game over.
        return 1;
    // Also, if the new coordinates would mean that the snake runs into itself...
    for (i = 0; i < sn - 2; i++){
        if (matr[i][0] == check1 && matr[i][1] == check2)
            // Game over.
            return 1;
    }
    
    // If the game is not over, move each piece to the spot occupied by the piece in front of it.
    for (i = 0; i < sn - 1; i++) {
        matr[i][0] = matr[i + 1][0];
        matr[i][1] = matr[i + 1][1];
    }
    // And move the head piece to (check1, check2).
    matr[sn - 1][0] = check1;
    matr[sn - 1][1] = check2;
    return 0;
}

/*******************************************************************************************************
 * Function name: End_Game
 * The input: A 2D matrix that contains the coordinates of the snake, the width of the rectangle, the
 *            height, and the length of the snake. 
 * The output: The function is void so it doesn't return anything. But it does print the end of game
 *             "animation."
 * The function operation: This function works very similarly to the function Print_Board, except that the
 *                         printing of the board is now in a loop that causes the function to print a new
 *                         board for every piece of the snake. In addition, the function uses the variable
 *                         "stars" to turn another piece of the snake into a star after each printing of
 *                         the board.
 *******************************************************************************************************/
void End_Game (int** matr, int w, int h, int sn){
    // First, print "Game Over".
    printf("Game Over\n");
    // These will be our counters for the four loops.
    int p, i, j, k;
    // snakePiece will do the same thing it did in the Print_Board function.
    int snakePiece = 0;
    // This variable will keep track of how many snake pieces we need to turn into stars on the current printing.
    int stars = 1;
    
    // A loop within a loop within a loop within a loop! HOW AWESOME IS THIS?
    for (p = 0; p < sn; p++){
        for (i = 0; i < h; i++){
            for (j = 0; j < w; j++){
                for (k = 0; k < sn; k ++){
                    // If the current spot on the board has the same coordinates as a piece of the snake...
                    if (matr[k][0] == i && matr[k][1] == j){
                        /*
                         * This inequality will turn the first piece into a star when stars equals 1, the first 
                         * two pieces into stars when stars equals 2, etc. Remember, the first piece of the snake
                         * (the head piece) is actually the last row in the 2D array and the last piece (the rear)
                         * is actually the first row in the 2D array.
                         */
                        if (sn - k <= stars)
                            printf("*");
                        else
                            // Otherwise, just print the regular big X or small x piece of the snake.
                            printf("%c", 'X' + matr[k][2]);
                        snakePiece = 1;
                        break;
                    }
                }
                // If you've already printed a snake piece in this spot, move on to the next spot on the board.
                if (snakePiece == 1){
                    snakePiece = 0;
                    continue;
                }
                // If we're in the first row or the last row...
                if (i == 0 || i == h - 1)
                    printf("-");
                // If we're not in the first row or last row, but we are in the first or last column...
                else if (j == 0 || j == w - 1)
                    printf("|");
                // If we're not in the first row, last row, first column, or last column...
                else
                    printf(".");
            }
            // New line after each row in the board.
            printf("\n");
        }
        // After printing each board, increment stars and skip another line.
        stars++;
        if (p < sn - 1)
            printf("\n");
    }
}

