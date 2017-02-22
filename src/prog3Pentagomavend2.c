#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COLUMN_NO 6
#define ROW_NO 6

void printBoard(char pentagoBoard[][COLUMN_NO]) {
	int rowPosition;
	int columnPosition;
	char letter = 65;
	printf("1   ");
	for (columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++) {
		printf("%d ", columnPosition + 1);
	}
	printf("  2\n");
	printf("    ");
	for (columnPosition = 1; columnPosition<COLUMN_NO * 2; columnPosition++) {
		printf("-");
	}
	printf("\n");
	for (rowPosition = 0; rowPosition<ROW_NO; rowPosition++) {
		printf("%c:  ", letter);
		for (columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++) {
			printf("%c ", pentagoBoard[rowPosition][columnPosition]);
		}
		printf(" :%c\n", letter);
		letter++;
	}
	printf("    ");
	for (columnPosition = 1; columnPosition<COLUMN_NO * 2; columnPosition++) {
		printf("-");
	}
	printf("\n");
	printf("3   ");
	for (columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++) {
		printf("%d ", columnPosition + 1);
	}
	printf("  4\n\n");

	return;
}//end printBoard function

void getUserMove(int turnNumber, char playerChar, char* rowInput, int* columnInput, int* quadrantInput, char* directionInput) {
	printf("%d. Enter row, column, quadrant, direction for %c: ", turnNumber, playerChar);
	scanf(" %c", rowInput);
	*rowInput = toupper(*rowInput);
	if (*rowInput == 'X') {
		return;
	}
	scanf(" %1d", columnInput);
	scanf(" %1d", quadrantInput);
	scanf(" %c", directionInput);
	*directionInput = toupper(*directionInput);
	return;
}//end getUserMove function

int validateMove(char rowInput, int columnInput, int quadrantInput, char directionInput, char pentagoBoard[][COLUMN_NO]) {
	int isValid;
	if ((rowInput < 65) || (rowInput >= 65 + ROW_NO)) {//if not A to char value of "A+number of rows"
		isValid = 1;
	}
	else if ((columnInput < 1) || (columnInput > COLUMN_NO)) {//return error if not between 1 and max number of columns
		isValid = 2;
	}
	else if ((quadrantInput < 1) || (quadrantInput > 4)) {//return error if not any of the 4 designated quadrants
		isValid = 3;
	}
	else if ((directionInput != 76) && (directionInput != 82)) {//return error if not L or R
		isValid = 4;
	}
	else if (pentagoBoard[rowInput - 65][columnInput - 1] != '.') {//spot on the board is already filled
		isValid = 5;
	}
	else {
		isValid = 0; //0 indicates a valid move!
	}
	return isValid;
}//end validateMove function

void printErrorMessage(int isValid) {
	if (isValid == 1) {
		printf("*** Invalid move row.  Please retry.\n");
	}
	else if (isValid == 2) {
		printf(" *** Invalid move column.  Please retry.\n");
	}
	else if (isValid == 3) {
		printf("*** Selected quadrant is invalid.  Please retry.\n");
	}
	else if (isValid == 4) {
		printf("*** Quadrant rotation direction is invalid.  Please retry.\n");
	}
	else if (isValid == 5) {
		printf("*** Spot already taken.  Please retry.\n");
	}
}//end printErrorMessage function

void makeMove(char pentagoBoard[][COLUMN_NO], char rowInput, int columnInput, char playerChar) {
	pentagoBoard[rowInput - 65][columnInput - 1] = playerChar;
}//end makeMove function

void rotateGameBoard(char pentagoBoard[][COLUMN_NO], int quadrantInput, char directionInput) {
	int i;
	int j;
	int k;
	int l;
	int temp;
	int startIValue;
	int startJValue;
	char quadMatrix[3][3];

	switch (quadrantInput) {
	case 1: startIValue = 0; startJValue = 0; break;
	case 2: startIValue = 0; startJValue = (COLUMN_NO / 2); break;
	case 3: startIValue = (ROW_NO / 2); startJValue = 0; break;
	case 4: startIValue = (ROW_NO / 2); startJValue = (COLUMN_NO / 2); break;
	default: i = 0; j = 0; break;
	}

	for (i = startIValue, k = 0; (i < startIValue + (ROW_NO / 2)) && (k<(ROW_NO / 2)); i++, k++) {
		for (j = startJValue, l = 0; (j < startJValue + (COLUMN_NO / 2)) && (l < (COLUMN_NO / 2)); j++, l++) {
			quadMatrix[k][l] = pentagoBoard[i][j];
			//printf("%d %d %d\n%d %d %d\n%d %d %d\n", quadMatrix[0][0], quadMatrix[0][1], quadMatrix[0][2], quadMatrix[1][0], quadMatrix[1][1], quadMatrix[1][2], quadMatrix[2][0], quadMatrix[2][1], quadMatrix[2][2]);
		}
	}

	for (k = 0; k < (ROW_NO / 2); k++) {
		for (l = k; l < (COLUMN_NO / 2); l++) {
			temp = quadMatrix[k][l];
			quadMatrix[k][l] = quadMatrix[l][k];
			quadMatrix[l][k] = temp;
		}
	}
	if (directionInput == 'L') {
		for (l = 0; l < (COLUMN_NO / 2); l++) { //Left Rotate
			k = 0;
			temp = quadMatrix[k][l];
			quadMatrix[k][l] = quadMatrix[(ROW_NO / 2) - 1][l];
			quadMatrix[(ROW_NO / 2) - 1][l] = temp;
		}
	}

	else {
		for (k = 0; k < (ROW_NO / 2); k++) { //Right Rotate
			l = 0;
			temp = quadMatrix[k][l];
			quadMatrix[k][l] = quadMatrix[k][(COLUMN_NO / 2) - 1];
			quadMatrix[k][(COLUMN_NO / 2) - 1] = temp;
		}
	}

	for (i = startIValue, k = 0; (i < startIValue + (ROW_NO / 2)) && (k<(ROW_NO / 2)); i++, k++) {
		for (j = startJValue, l = 0; (j < startJValue + (COLUMN_NO / 2)) && (l < (COLUMN_NO / 2)); j++, l++) {
			pentagoBoard[i][j] = quadMatrix[k][l];
		}
	}
}//end rotateGameBoard function

void checkWinCondition(char pentagoBoard[][COLUMN_NO], int* countX, int* countCircle) {
	int diagonalSlice;
	int diagonalNum;
	int row;
	int column;
	int counter;
	for (row = 0; row < ROW_NO; row++) {//count rows for five in row for X
		counter = 0; //reset to 0 for the new row
		for (column = 0; column < COLUMN_NO; column++) {
			if (pentagoBoard[row][column] == 'X') {
				counter++;
			}
			else {
				counter = 0; //start over from 0
			}
			if (counter == 5) {
				*countX = counter;
				break; //stop counting but keep going to check for a tie;
			}
		}
	}
	for (row = 0; row < ROW_NO; row++) {//count rows for five in row for O this time
		counter = 0; //reset to 0 for the new row
		for (column = 0; column < COLUMN_NO; column++) {
			if (pentagoBoard[row][column] == 'O') {
				counter++;
			}
			else {
				counter = 0; //start over from 0
			}
			if (counter == 5) {
				*countCircle = counter;
				break; //stop counting but keep going to check for a tie;
			}
		}
	}
	if (*countX != 5) {
		for (column = 0; column < COLUMN_NO; column++) {//count columns for five in row for X
			counter = 0; //reset to zero for the new column
			for (row = 0; row < ROW_NO; row++) {
				if (pentagoBoard[row][column] == 'X') {
					counter++;
				}
				else {
					counter = 0; //start over from 0
				}
				if (counter == 5) {
					*countX = counter;
					break; //stop counting but keep going to check for a tie;
				}
			}
		}
	}
	if (*countCircle != 5) {
		for (column = 0; column < COLUMN_NO; column++) {//count columns for five in row for O
			counter = 0;
			for (row = 0; row < ROW_NO; row++) {
				if (pentagoBoard[row][column] == 'O') {
					counter++;
				}
				else {
					counter = 0; //start over from 0
				}
				if (counter == 5) {
					*countCircle = counter;
					break; //stop counting but keep going to check for a tie;
				}
			}
		}
	}
	if (*countX != 5) {
		for (diagonalSlice = 0; diagonalSlice < (ROW_NO * 2) - 1; diagonalSlice++) {//picks the diagonal slice
			counter = 0;
			diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1; //number to hold the phase
			for (row = diagonalNum; row <= diagonalSlice - diagonalNum; row++) {
				if (pentagoBoard[row][diagonalSlice - row] == 'X') { // check diagonal from top right to bottom left
					counter++;
				}
				else {
					counter = 0;
				}
				if (counter == 5) {
					*countX = counter;
					break;
				}
			}
		}
	}
	if (*countX != 5) {
		for (diagonalSlice = 0; diagonalSlice < (ROW_NO * 2) - 1; diagonalSlice++) {
			counter = 0;
			diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1;
			for (row = diagonalNum; row <= diagonalSlice - diagonalNum; row++) {
				if (pentagoBoard[row][(ROW_NO - 1) - (diagonalSlice - row)] == 'X') { //check diagonal from top left to bottom right
					counter++;
				}
				else {
					counter = 0;
				}
				if (counter == 5) {
					*countX = counter;
					break;
				}
			}
		}
	}
	if (*countCircle != 5) {
		for (diagonalSlice = 0; diagonalSlice < (ROW_NO * 2) - 1; diagonalSlice++) {//picks the diagonal slice
			counter = 0;
			diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1; //number to hold the phase
			for (row = diagonalNum; row <= diagonalSlice - diagonalNum; row++) {
				if (pentagoBoard[row][diagonalSlice - row] == 'O') { // check diagonal from top right to bottom left
					counter++;
				}
				else {
					counter = 0;
				}
				if (counter == 5) {
					*countCircle = counter;
					break;
				}
			}
		}
	}
	if (*countCircle != 5) {
		for (diagonalSlice = 0; diagonalSlice < (ROW_NO * 2) - 1; diagonalSlice++) {
			counter = 0;
			diagonalNum = diagonalSlice < (ROW_NO) ? 0 : diagonalSlice - ROW_NO + 1;
			for (row = diagonalNum; row <= diagonalSlice - diagonalNum; row++) {
				if (pentagoBoard[row][(ROW_NO - 1) - (diagonalSlice - row)] == 'O') { //check diagonal from top left to bottom right
					counter++;
				}
				else {
					counter = 0;
				}
				if (counter == 5) {
					*countCircle = counter;
					break;
				}
			}
		}
	}
	return;
}//end checkWinCondition function

int checkForEmptySpace(char pentagoBoard[][COLUMN_NO]) {
	int row;
	int column;
	int isEmpty = 0;
	for (row = 0; row < ROW_NO; row++) {
		for (column = 0; column < COLUMN_NO; column++) {
			if (pentagoBoard[row][column] == '.') {
				isEmpty = 1;
				break;
			}
		}
	}
	return isEmpty;
}

void printWinMessage(int countX, int countCircle) {
	if (countX == 5 && countCircle != 5) { //if only X got 5 in a row
		printf("X has won the game!\n\n");
	}
	else if (countX != 5 && countCircle == 5) { //if only O got 5 in a row
		printf("O has won the game!\n\n");
	}
	else { //otherwise a tie
		printf("The game was a tie!\n\n");
	}
	system("pause");
}//end printWinMessage function

int main(void) {
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
	for (rowPosition = 0; rowPosition<ROW_NO; rowPosition++) {  //initialize 6x6 array with 36 dots
		for (columnPosition = 0; columnPosition<COLUMN_NO; columnPosition++) {
			pentagoBoard[rowPosition][columnPosition] = 46;
		}
	}//end initializing
	while (1) {
		printBoard(pentagoBoard);
		getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);
		if (userRowInput == 'X') {
			printf("Exiting program...\n");
			return 0;
		}
		isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput, pentagoBoard);

		while (isValid != 0) {
			printErrorMessage(isValid);
			getUserMove(turnNumber, playerChar, &userRowInput, &userColumnInput, &userQuadrantInput, &userDirectionInput);
			if (userRowInput == 'X') {
				printf("Exiting program...\n");
				return 0;
			}
			isValid = validateMove(userRowInput, userColumnInput, userQuadrantInput, userDirectionInput, pentagoBoard);
		}
		makeMove(pentagoBoard, userRowInput, userColumnInput, playerChar);
		checkWinCondition(pentagoBoard, &countX, &countCircle);
		if (countX == 5 || countCircle == 5) {
			printf("\n");
			break;
		}
		rotateGameBoard(pentagoBoard, userQuadrantInput, userDirectionInput);
		checkWinCondition(pentagoBoard, &countX, &countCircle);
		isEmpty = checkForEmptySpace(pentagoBoard);
		if (countX == 5 || countCircle == 5 || isEmpty == 0) {
			printf("\n");
			break;
		}
		turnNumber++;
		if (turnNumber % 2 == 0) {
			playerChar = 'O';
		}
		else {
			playerChar = 'X';
		}
		printf("\n");
	}
	printWinMessage(countX, countCircle);
	printBoard(pentagoBoard);
	printf("Thanks for playing.  Exiting...\n\n");
	system("pause");
	return 0;
}