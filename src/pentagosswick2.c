#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COLUMN_NO 6
#define ROW_NO 6

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
        printf("*** Spot already taken.  Please retry.\n")
    }
}//end printErrorMessage function

void makeMove(char pentagoBoard[][COLUMN_NO], char rowInput, int columnInput, char playerChar){
    pentagoBoard[rowInput - 65][columnInput - 1] = playerChar;
}//end makeMove function

int main(void){
    int rowPosition;
    int columnPosition;
    int turnNumber = 1;
    char playerChar = 'X';
    char userRowInput; //decalre variables to hold user input
    int userColumnInput;
    int userQuadrantInput;
    char userDirectionInput;
    int isValid; //declare variable to check if valid move
    char pentagoBoard[ROW_NO][COLUMN_NO];
    for(rowPosition = 0; rowPosition<ROW_NO; rowPosition++){  //initialize 6x6 array with 36 dots
        for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
            pentagoBoard[rowPosition][columnPosition] = 46;
        }
    }//end initializing
    printBoard(pentagoBoard);
    getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);
    isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput);
    while(isValid != 0){
        printErrorMessage(isValid);
        getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);
        isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput);
    }
    makeMove(pentagoBoard, userRowInput, userColumnInput, playerChar);
    printBoard(pentagoBoard);
    turnNumber++;
    if(turnNumber%2 == 0){
        playerChar = 'O';
    }
    else{
        playerChar = 'X';
    }
    return 0;
}
