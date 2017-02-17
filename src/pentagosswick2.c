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

void getUserMove(int turnNumber, char* rowInput, int* columnInput, int* quadrantInput, char* directionInput){
    printf("%d. Enter row, column, quadrant, direction for X: ", turnNumber);
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
}


int main(void){
    int rowPosition;
    int columnPosition;
    int turnNumber = 1;
    char userRowInput;
    int userColumnInput;
    int userQuadrantInput;
    char userDirectionInput;
    char pentagoBoard[ROW_NO][COLUMN_NO];
    for(rowPosition = 0; rowPosition<ROW_NO; rowPosition++){//initialize 6x6 array with 36 dots
        for(columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++){
            pentagoBoard[rowPosition][columnPosition] = 46;
        }
    }//end initializing
    printBoard(pentagoBoard);
    getUserMove(turnNumber, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);
    return 0;
}
