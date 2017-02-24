#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COLUMN_NO 6 //Change this number to increase or decrease the number of columns
#define ROW_NO 6 //Change this number to increase or decrease the number of rows

/*-------------------------------------------------------------------
 * Prog #3: Pentago
 *
 * Class: CS 141, Spring 2017.  Tues 11AM, 2PM Labs
 * System: Ubuntu 16.04, Code::Blocks; Windows, Visual Studio
 * Author: Mike Avendano & Stephen Swick
 *
 * Program that will execute the game of pentago.  Basically
 * tic tac toe but one must get 5 in a row, and the board is
 * split into 4 quadrants that rotate either left or right
 * per players' turn.  Current program is scaleable for
 * even squared boards. I.E. 2 rows 2 columns, 4 rows, 4 columns
 * and etc.  Due to how the rotate function is programmed if you were
 * to use a 7x7 board the quadrants would have an uneven division
 * and some of the values would be deleted during rotation.
 *--------------------------------------------------------------------
 */

 //Function that will print students info at the start of the program
void printInfo(void){
    printf("Author: Michael Avendano & Stephen Swick\n");
    printf("Program: #3, Pentago\n");
    printf("TA: Moumita Samanta, Tues 2PM, 11AM\n");
    printf("Feb 27, 2017\n\n");
}

//Function that will print out game instructions at the beginning of the program.
void printInstructions(void){
    printf("Play the two-player game of Pentago. Be the first to get 5 in a row.\n\n");
    printf("Pentago is played on a 6 by 6 board, divided into four 3 by 3\n");
    printf("quadrants.  There are two players, X and O, who alternate turns.\n");
    printf("The goal of each player is to get five of their pieces in a row,\n");
    printf("either horizontally, vertically, or diagonally.\n\n");

    printf("Players take turns placing one of their pieces into an empty\n");
    printf("space anywhere on the board, then choosing one of the four\n");
    printf("board quadrants to rotate 90 degrees left or right.\n\n");

    printf("If both players get five in a row at the same time, or the\n");
    printf("last move is played with no five in a row, the game is a tie.\n");
    printf("If a player makes five a row by placing a piece, there is no need\n");
    printf("to rotate a quadrant and the player wins immediately.\n\n");

    printf("Play online at:  https://perfect-pentago.net\n");
    printf("Purchase at:     www.mindtwisterusa.com\n\n");

    printf("For each move provide four inputs:\n");
    printf("row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R)\n");
    printf("For instance input of B32R places the next piece at B3 and then\n");
    printf("would rotate quadrant 3 (lower-left) to the right (clockwise).\n\n");

    printf("At any point enter 'x' to exit the program.\n\n");
}

/*--------------------------------------------------------
 * Functio that will print the board.  This function in
 * theory is able to print out boards smaller than the
 * 6x6 and bigger than the 6x6 required for this program.
 * Takes a double array that is supposed to represent the
 * pentago board as a parameter.  The function will loop
 * through the elements of the array and print out the
 * value of that element which can be either a empty spot
 * represented as a dot, an 'X', or an 'O'.
 *--------------------------------------------------------
 */
void printBoard(char pentagoBoard[][COLUMN_NO]){
    int rowPosition;
    int columnPosition;
    char letter = 65; //start at A
    printf("1   "); //quadrant 1
    for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){ //print 1 - 6 at the top of the board, scales up to how many columns you want
        printf("%d ", columnPosition+1);
    }
    printf("  2\n"); // quadrant 2
    printf("    ");
    for(columnPosition = 1; columnPosition<COLUMN_NO*2; columnPosition++){  //print appropriate amount of dashes
        printf("-");
    }
    printf("\n");
    for(rowPosition = 0; rowPosition<ROW_NO; rowPosition++){ // begin printing the elements of the double array
        printf("%c:  ", letter); //print the letter of the row
        for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
            printf("%c ", pentagoBoard[rowPosition][columnPosition]); // print element of thedouble array
        }
        printf(" :%c\n", letter); //print the letter of the row
        letter++; //add one to letter, I.E go from A to B and so on
    }
    printf("    ");
    for(columnPosition = 1; columnPosition<COLUMN_NO*2; columnPosition++){
        printf("-");
    }
    printf("\n");
    printf("3   "); // 3rd quadrant
    for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
        printf("%d ", columnPosition+1);
    }
    printf("  4\n\n"); // 4th quadrant

    return;
}//end printBoard function

/*------------------------------------------------------
 * Function that scans the users inputs.  Will stop
 * scanning and only return X for exit out of program
 * if user enters 'X'.  Scan will only scan 1 width
 * of letters/integers, and the letters will be
 * capitalized using toupper function.  For this reason
 * the code must be modified here if you are scaling the
 * board to have double digit columns.
 *------------------------------------------------------
 */
void getUserMove(int turnNumber, char playerChar, char* rowInput, int* columnInput, int* quadrantInput, char* directionInput){
    printf("%d. Enter row, column, quadrant, direction for %c: ", turnNumber, playerChar);
    scanf(" %1c", rowInput); //scan only ONE char
    *rowInput = toupper(*rowInput);
    if (*rowInput == 'X'){
        return;  //stop the function, just exit out
    }
    scanf(" %1d", columnInput); //scan only ONE int DIGIT
    scanf(" %1d", quadrantInput); //scan only ONE char
    scanf(" %1c", directionInput); // scan only ONE int DIGIT
    *directionInput = toupper(*directionInput);
    return;
}//end getUserMove function

/*-----------------------------------------------------------------------
 * Function that will take user inputs and make sure they are a valid
 * move.  It will check to make sure the input for row is in bounds.
 * the input for column is in bounds.  The quadrant input is in bounds.
 * The direction input is either L or R.  And finally make sure the
 * spot on the board isnt taken.  In that order.  Will return an int
 * variable for futher use.  I.E. will call the next function and
 * return an error message.  And also the function call in main
 * will keep repeating until isValid is equal to zero, meaning a valid
 * move.
 *-----------------------------------------------------------------------
 */
int validateMove(char rowInput, int columnInput, int quadrantInput, char directionInput, char pentagoBoard[][COLUMN_NO]){
    int isValid;
    if ((rowInput < 65) || (rowInput >= 65+ROW_NO)){//if not A to char value of "A+number of rows"
        isValid = 1;
    }
    else if((columnInput < 1) || (columnInput > COLUMN_NO)){//return error if not between 1 and max number of columns
        isValid = 2;
    }
    else if((quadrantInput < 1) || (quadrantInput > 4)){//return error if not any of the 4 designated quadrants
        isValid = 3;
    }
    else if((directionInput != 76) && (directionInput != 82)){//return error if not L or R
        isValid = 4;
    }
    else if(pentagoBoard[rowInput - 65][columnInput - 1] != '.'){//spot on the board is already filled
        isValid = 5;
    }
    else{
        isValid = 0; //0 indicates a valid move!
    }
    return isValid;
}//end validateMove function

// Function that just prints out the error message corresponding to the invalid move made
// Takes the int value that was returned from the validateMove function
void printErrorMessage(int isValid){
    if(isValid == 1){
        printf("*** Invalid move row.  Please retry.\n");
    }
    else if(isValid == 2){
        printf(" *** Invalid move column.  Please retry.\n");
    }
    else if(isValid == 3){
        printf("*** Selected quadrant is invalid.  Please retry.\n");
    }
    else if(isValid == 4){
        printf("*** Quadrant rotation direction is invalid.  Please retry.\n");
    }
    else if(isValid == 5){
        printf("*** That board location is already taken.  Please retry.\n");
    }
}//end printErrorMessage function

//Simple function to make the move, will be called in main when the move is validated to be a valid move
void makeMove(char pentagoBoard[][COLUMN_NO], char rowInput, int columnInput, char playerChar){
    pentagoBoard[rowInput - 65][columnInput - 1] = playerChar; //column is offset by 1, so just subtract by 1, row is offset by A subtract by A
}//end makeMove function

/*------------------------------------------------------------------------------------------------------------
*Function divides the gameboard into 4 quadrants and rotates the chosen quadrant based
*on the user input. Function will take in the gameboard array, the quadarant the player is referring 
*to, and the direction. The quadrant input specifies where in the gameboard the rotate should start. 
*The function then takes the transpose of the specified 3x3 quadrant. The direction input is used to determine
*whether a left rotate happens and the rows are switched or a right rotate happens and the columns 
* are switched. The final loop inserts the rotated quadrant back into the original gameboard. 
*
*Left Rotate Example:
*      transpose         left rotate (rows 1 and 3 are switched)
* 123              147          369
* 456     -->      258    -->   258
* 789              369          147  
*
*------------------------------------------------------------------------------------------------------------
*/

void rotateGameBoard(char pentagoBoard[][COLUMN_NO], int quadrantInput, char directionInput) {
	int row;
	int column;
	int temp;
	int startRowValue;
	int startColumnValue;
	char quadMatrix[ROW_NO/2][COLUMN_NO/2];

	switch (quadrantInput) {
	case 1: startRowValue = 0; startColumnValue = 0; break;
	case 2: startRowValue = 0; startColumnValue = (COLUMN_NO / 2); break;
	case 3: startRowValue = (ROW_NO / 2); startColumnValue = 0; break;
	case 4: startRowValue = (ROW_NO / 2); startColumnValue = (COLUMN_NO / 2); break;
	}

	for (row = 0; row < (ROW_NO / 2); row++) {
		for (column = 0; column < (COLUMN_NO / 2); column++) {
			quadMatrix[row][column] = pentagoBoard[row + startRowValue][column + startColumnValue];
			}
	}

	for (row = 0; row < (ROW_NO / 2); row++) {
		for (column = row; column < (COLUMN_NO / 2); column++) {
			temp = quadMatrix[row][column];
			quadMatrix[row][column] = quadMatrix[column][row];
			quadMatrix[column][row] = temp;
		}
	}
	if (directionInput == 'L') {
		for (column = 0; column < (COLUMN_NO / 2); column++) { //Left Rotate
			row = 0;
			temp = quadMatrix[row][column];
			quadMatrix[row][column] = quadMatrix[(ROW_NO / 2) - 1][column];
			quadMatrix[(ROW_NO / 2) - 1][column] = temp;
		}
	}

	else {
		for (row = 0; row < (ROW_NO / 2); row++) { //Right Rotate
			column = 0;
			temp = quadMatrix[row][column];
			quadMatrix[row][column] = quadMatrix[row][(COLUMN_NO / 2) - 1];
			quadMatrix[row][(COLUMN_NO / 2) - 1] = temp;
		}
	}

	for (row = 0; row<(ROW_NO / 2); row++) {
		for (column = 0; column < (COLUMN_NO / 2); column++) {
			pentagoBoard[row + startRowValue][column + startColumnValue] = quadMatrix[row][column];
		}
	}
}//End RotateGameBoard

/*---------------------------------------------------------------------
 * Function that will check the board for five in a row.  Takes in
 * 2 parameters, the board and the character you want to check.  I.e.
 * an X or an O.  Will first check the rows of the board.  Does this by
 * increment the row variable by 1 after it checks all the columns.
 * Likewise does the same for checking columns, but just keeping the
 * column variable constant while checking all the rows.  Next will
 * check the diagonals.  Have 2 loops for this.  One to check the
 * diagonals from top left to bottom right.  And another to check from
 * top right to bottom left.  Function will return and stop counting
 * based on the first detection of 5 in a row.
 *---------------------------------------------------------------------
 */
int checkWinCondition(char pentagoBoard[][COLUMN_NO], char playerChar){
    int diagonalSlice;
    int diagonalModificationNumber;
    int row;
    int column;
    int counter;
    for(row = 0; row < ROW_NO; row++){//count rows for five in row for X
        counter = 0; //reset to 0 for the new row
        for(column = 0; column < COLUMN_NO; column++){
            if(pentagoBoard[row][column] == playerChar){
                counter++;
            }
            else{
                counter = 0; //start over from 0
            }
            if(counter == 5){
                return counter;
            }
        }
    }
    for(column = 0; column < COLUMN_NO; column++){//count columns for five in row for X
        counter = 0; //reset to zero for the new column
        for(row = 0; row < ROW_NO; row++){
            if(pentagoBoard[row][column] == playerChar){
                counter++;
            }
            else{
                counter = 0; //start over from 0
            }
            if(counter == 5){
                return counter;
            }
        }
    }
    for(diagonalSlice = 0; diagonalSlice < (ROW_NO*2)-1; diagonalSlice++){//picks the diagonal slice
        counter = 0;
        diagonalModificationNumber = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1; //number to hold the phase
        for(row = diagonalModificationNumber; row <= diagonalSlice - diagonalModificationNumber; row++){
            if(pentagoBoard[row][diagonalSlice - row] == playerChar){ // check diagonal from top right to bottom left
                counter++;
            }
            else{
                counter = 0;
            }
            if(counter == 5){
                return counter;
            }
        }
    }
    for(diagonalSlice = 0; diagonalSlice < (ROW_NO*2)-1; diagonalSlice++){
        counter = 0;
        diagonalModificationNumber = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1;
        for(row = diagonalModificationNumber; row <= diagonalSlice - diagonalModificationNumber; row++){
            if(pentagoBoard[row][(ROW_NO - 1) - (diagonalSlice - row)] == playerChar){ //check diagonal from top left to bottom right
                counter++;
            }
            else{
                counter = 0;
            }
            if(counter == 5){
                return counter;
            }
        }
    }
    return counter;
}//end checkWinCondition function

//function that will print message based on who won or if a tie
void printWinMessage(int countX, int countCircle){
    if(countX == 5 && countCircle != 5){ //if only X got 5 in a row
        printf("X has won the game!\n\n");
    }
    else if(countX != 5 && countCircle == 5){ //if only O got 5 in a row
        printf("O has won the game!\n\n");
    }
    else{ //otherwise a tie
        printf("The game was a tie!\n\n");
    }
}//end printWinMessage function

//main function that structures the program together will call all functions in a order to run the game
int main(void){
    int rowPosition; // variables for initialization
    int columnPosition; // variables for initialization
    int turnNumber = 1;  // variable to represent turn number
    char playerChar = 'X';
    int countX = 0; //variable to count for 5 X's in a row
    int countCircle = 0; //variable to count for 5 O's in a row
    char userRowInput; //decalre variables to hold user input
    int userColumnInput;
    int userQuadrantInput;
    char userDirectionInput;
    int isValid; //declare variable to check if valid move
    char pentagoBoard[ROW_NO][COLUMN_NO];
    // finish creating variables used for program
    printInfo(); // begin program by printing student info
    printInstructions(); //print out instructions for game and source of game
    for(rowPosition = 0; rowPosition<ROW_NO; rowPosition++){  //initialize 6x6 array with 36 dots
        for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
            pentagoBoard[rowPosition][columnPosition] = 46;
        }
    }//end initializing
    while(1){  //infinite loop, keep running programming until win condition or variable to exit program is inputed
        printBoard(pentagoBoard); //print board first
        getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);  // prompt user for move
        if(userRowInput == 'X'){  //close program if the user inputs 'X'
            printf("\nExiting program...\n");
            return 0;
        }
        isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput, pentagoBoard);  //validate move

        while(isValid != 0){  // keep looping until valid move is made
            printErrorMessage(isValid);  // first print error message according to which error
            getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);  // prompt for another move
            if(userRowInput == 'X'){  //make sure if they want to exit out of program instead
                printf("\nExiting program...\n");
                return 0;
            }
            isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput, pentagoBoard); //validate move again
        }
        makeMove(pentagoBoard, userRowInput, userColumnInput, playerChar);  //move is valid so modify board
        countX = checkWinCondition(pentagoBoard, 'X');  // count for X before rotate
        countCircle = checkWinCondition(pentagoBoard, 'O'); // count for O before rotate
        if(countX == 5 || countCircle == 5){  //break out of loop once detect 5 in a row dont rotate the board end game
            printf("\n");
            break;
        }
        rotateGameBoard(pentagoBoard, userQuadrantInput, userDirectionInput);  //rotate board
        countX = checkWinCondition(pentagoBoard, 'X'); //count for X after rotation
        countCircle = checkWinCondition(pentagoBoard, 'O'); //count for O after rotation
        if(countX == 5 || countCircle == 5 || turnNumber == 36){  //break out of loop if 5 in row after rotate or if theres no more spots on the board (i.e. turn 36)
            printf("\n");
            break;
        }
        turnNumber++;  //game not over? increment turn by 1
        if(turnNumber%2 == 0){  //if even turn, its O's turn
            playerChar = 'O';
        }
        else{
            playerChar = 'X'; //if odd turn X's turn
        }
        printf("\n");  // newline for format
    }
    printWinMessage(countX, countCircle);  //game is done, print out result
    printBoard(pentagoBoard); //print the board one last time
    printf("Thanks for playing.  Exiting...\n\n"); //bye bye
    return 0;
} //end main
