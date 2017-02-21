#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COLUMN_NO 6
#define ROW_NO 6

void printInfo(void){
    printf("Author: Michael Avendano & Stephen Swick\n");
    printf("Program: #3, Pentago\n");
    printf("TA: Moumita Samanta, Tues 2PM, 11AM\n");
    printf("Feb 27, 2017\n\n");
}

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

void printBoard(char pentagoBoard[][COLUMN_NO]){
    int rowPosition;
    int columnPosition;
    char letter = 65;
    printf("1   ");
    for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
        printf("%d ", columnPosition+1);
    }
    printf("  2\n");
    printf("    ");
    for(columnPosition = 1; columnPosition<COLUMN_NO*2; columnPosition++){
        printf("-");
    }
    printf("\n");
    for(rowPosition = 0; rowPosition<ROW_NO; rowPosition++){
        printf("%c:  ", letter);
        for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
            printf("%c ", pentagoBoard[rowPosition][columnPosition]);
        }
        printf(" :%c\n", letter);
        letter++;
    }
    printf("    ");
    for(columnPosition = 1; columnPosition<COLUMN_NO*2; columnPosition++){
        printf("-");
    }
    printf("\n");
    printf("3   ");
    for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
        printf("%d ", columnPosition+1);
    }
    printf("  4\n\n");

    return;
}//end printBoard function

void getUserMove(int turnNumber, char playerChar, char* rowInput, int* columnInput, int* quadrantInput, char* directionInput){
    printf("%d. Enter row, column, quadrant, direction for %c: ", turnNumber, playerChar);
    scanf(" %c", rowInput);
    *rowInput = toupper(*rowInput);
    if (*rowInput == 'X'){
        return;
    }
    scanf(" %1d", columnInput);
    scanf(" %1d", quadrantInput);
    scanf(" %c", directionInput);
    *directionInput = toupper(*directionInput);
    return;
}//end getUserMove function

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
        printf("*** Spot already taken.  Please retry.\n");
    }
}//end printErrorMessage function

void makeMove(char pentagoBoard[][COLUMN_NO], char rowInput, int columnInput, char playerChar){
    pentagoBoard[rowInput - 65][columnInput - 1] = playerChar;
}//end makeMove function

void rotateGameBoard(char pentagoBoard[][COLUMN_NO], int quadrantInput, char directionInput){
    int row;
    int column;
    char pentagoBoardCopy[ROW_NO][COLUMN_NO];//make a copy of the board to hold the values
    for(row = 0; row < ROW_NO; row++){  //initialize copy of array with the original board
        for(column = 0; column < COLUMN_NO; column++){
            pentagoBoardCopy[row][column] = pentagoBoard[row][column];
        }
    }
    if(quadrantInput == 1){
        if(directionInput == 'R'){
            for(row = 0; row < (ROW_NO/2); row++){
                for(column = 0; column < (COLUMN_NO/2); column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[(ROW_NO/2) - column - 1][row];
                }
            }
        }
        else{
            for(row = 0; row < ROW_NO/2; row++){
                for(column = 0; column < COLUMN_NO/2; column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[column][(COLUMN_NO/2) - row - 1];
                }
            }
        }
    }
    else if (quadrantInput == 2){
        if(directionInput == 'R'){
            for(row = 0; row < (ROW_NO/2); row++){
                for(column = (COLUMN_NO/2); column < COLUMN_NO; column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[(ROW_NO) - column - 1][(COLUMN_NO/2) + row];
                }
            }
        }
        else{
            for(row = 0; row < ROW_NO/2; row++){
                for(column = COLUMN_NO/2; column < COLUMN_NO; column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[column - (ROW_NO/2)][(COLUMN_NO) - row - 1];
                }
            }
        }
    }
    else if (quadrantInput == 3){
        if(directionInput == 'R'){
            for(row = ROW_NO/2; row < ROW_NO; row++){
                for(column = 0; column < COLUMN_NO/2; column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[(ROW_NO) - column - 1][row - (COLUMN_NO/2)];
                }
            }
        }
        else{
            for(row = ROW_NO/2; row < ROW_NO; row++){
                for(column = 0; column < COLUMN_NO/2; column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[(ROW_NO/2) + column][(COLUMN_NO) - row - 1];
                }
            }
        }
    }
    else if (quadrantInput == 4){
        if(directionInput == 'R'){
            for(row = ROW_NO/2; row < ROW_NO; row++){
                int count = 0;
                for(column = COLUMN_NO/2; column < COLUMN_NO; column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[ROW_NO - count - 1][row];
                    count++;
                }
            }
        }
        else{
            int count = 0;
            for(row = ROW_NO/2; row < ROW_NO; row++){
                for(column = COLUMN_NO/2; column < COLUMN_NO; column++){
                    pentagoBoard[row][column] = pentagoBoardCopy[column][(COLUMN_NO) - count - 1];
                }
                count++;
            }
        }
    }
}//end rotateGameBoard function

void checkWinCondition(char pentagoBoard[][COLUMN_NO], int* countX, int* countCircle){
    int diagonalSlice;
    int diagonalNum;
    int row;
    int column;
    int counter;
    for(row = 0; row < ROW_NO; row++){//count rows for five in row for X
        counter = 0; //reset to 0 for the new row
        for(column = 0; column < COLUMN_NO; column++){
            if(pentagoBoard[row][column] == 'X'){
                counter++;
            }
            else{
                counter = 0; //start over from 0
            }
            if(counter == 5){
                *countX = counter;
                break; //stop counting but keep going to check for a tie;
            }
        }
    }
    for(row = 0; row < ROW_NO; row++){//count rows for five in row for O this time
        counter = 0; //reset to 0 for the new row
        for(column = 0; column < COLUMN_NO; column++){
            if(pentagoBoard[row][column] == 'O'){
                counter++;
            }
            else{
                counter = 0; //start over from 0
            }
            if(counter == 5){
                *countCircle = counter;
                break; //stop counting but keep going to check for a tie;
            }
        }
    }
    if(*countX != 5){
        for(column = 0; column < COLUMN_NO; column++){//count columns for five in row for X
            counter = 0; //reset to zero for the new column
            for(row = 0; row < ROW_NO; row++){
                if(pentagoBoard[row][column] == 'X'){
                    counter++;
                }
                else{
                    counter = 0; //start over from 0
                }
                if(counter == 5){
                    *countX = counter;
                    break; //stop counting but keep going to check for a tie;
                }
            }
        }
    }
    if(*countCircle != 5){
        for(column = 0; column < COLUMN_NO; column++){//count columns for five in row for O
            counter = 0;
            for(row = 0; row < ROW_NO; row++){
                if(pentagoBoard[row][column] == 'O'){
                    counter++;
                }
                else{
                    counter = 0; //start over from 0
                }
                if(counter == 5){
                    *countCircle = counter;
                    break; //stop counting but keep going to check for a tie;
                }
            }
        }
    }
    if(*countX != 5){
        for(diagonalSlice = 0; diagonalSlice < (ROW_NO*2)-1; diagonalSlice++){//picks the diagonal slice
            counter = 0;
            diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1; //number to hold the phase
            for(row = diagonalNum; row <= diagonalSlice - diagonalNum; row++){
                if(pentagoBoard[row][diagonalSlice - row] == 'X'){ // check diagonal from top right to bottom left
                    counter++;
                }
                else{
                    counter = 0;
                }
                if(counter == 5){
                    *countX = counter;
                    break;
                }
            }
        }
    }
    if(*countX != 5){
        for(diagonalSlice = 0; diagonalSlice < (ROW_NO*2)-1; diagonalSlice++){
            counter = 0;
            diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1;
            for(row = diagonalNum; row <= diagonalSlice - diagonalNum; row++){
                if(pentagoBoard[row][(ROW_NO - 1) - (diagonalSlice - row)] == 'X'){ //check diagonal from top left to bottom right
                    counter++;
                }
                else{
                    counter = 0;
                }
                if(counter == 5){
                    *countX = counter;
                    break;
                }
            }
        }
    }
    if(*countCircle != 5){
        for(diagonalSlice = 0; diagonalSlice < (ROW_NO*2)-1; diagonalSlice++){//picks the diagonal slice
            counter = 0;
            diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1; //number to hold the phase
            for(row = diagonalNum; row <= diagonalSlice - diagonalNum; row++){
                if(pentagoBoard[row][diagonalSlice - row] == 'O'){ // check diagonal from top right to bottom left
                    counter++;
                }
                else{
                    counter = 0;
                }
                if(counter == 5){
                    *countCircle = counter;
                    break;
                }
            }
        }
    }
    if(*countCircle != 5){
        for(diagonalSlice = 0; diagonalSlice < (ROW_NO*2)-1; diagonalSlice++){
            counter = 0;
            diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1;
            for(row = diagonalNum; row <= diagonalSlice - diagonalNum; row++){
                if(pentagoBoard[row][(ROW_NO - 1) - (diagonalSlice - row)] == 'O'){ //check diagonal from top left to bottom right
                    counter++;
                }
                else{
                    counter = 0;
                }
                if(counter == 5){
                    *countCircle = counter;
                    break;
                }
            }
        }
    }
    return;
}//end checkWinCondition function

int checkForEmptySpace(char pentagoBoard[][COLUMN_NO]){
    int row;
    int column;
    int isEmpty = 0;
    for(row = 0; row < ROW_NO; row++){
        for(column = 0; column < COLUMN_NO; column++){
            if(pentagoBoard[row][column] == '.'){
                isEmpty = 1;
                break;
            }
        }
    }
    return isEmpty;
}

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

int main(void){
    int rowPosition;
    int columnPosition;
    int turnNumber = 1;
    char playerChar = 'X';
    int countX = 0;
    int countCircle = 0;
    int isEmpty;
    char userRowInput; //decalre variables to hold user input
    int userColumnInput;
    int userQuadrantInput;
    char userDirectionInput;
    int isValid; //declare variable to check if valid move
    char pentagoBoard[ROW_NO][COLUMN_NO];
    printInfo();
    printInstructions();
    for(rowPosition = 0; rowPosition<ROW_NO; rowPosition++){  //initialize 6x6 array with 36 dots
        for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
            pentagoBoard[rowPosition][columnPosition] = 46;
        }
    }//end initializing
    while(1){
        printBoard(pentagoBoard);
        getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);
        if(userRowInput == 'X'){
            printf("Exiting program...\n");
            return 0;
        }
        isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput, pentagoBoard);

        while(isValid != 0){
            printErrorMessage(isValid);
            getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);
            if(userRowInput == 'X'){
                printf("Exiting program...\n");
                return 0;
            }
            isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput, pentagoBoard);
        }
        makeMove(pentagoBoard, userRowInput, userColumnInput, playerChar);
        checkWinCondition(pentagoBoard, &countX, &countCircle);
        if(countX == 5 || countCircle == 5){
            printf("\n");
            break;
        }
        rotateGameBoard(pentagoBoard, userQuadrantInput, userDirectionInput);
        checkWinCondition(pentagoBoard, &countX, &countCircle);
        isEmpty = checkForEmptySpace(pentagoBoard);
        if(countX == 5 || countCircle == 5 || isEmpty == 0){
            printf("\n");
            break;
        }
        turnNumber++;
        if(turnNumber%2 == 0){
            playerChar = 'O';
        }
        else{
            playerChar = 'X';
        }
        printf("\n");
    }
    printWinMessage(countX, countCircle);
    printBoard(pentagoBoard);
    printf("Thanks for playing.  Exiting...\n\n");
    return 0;
}
