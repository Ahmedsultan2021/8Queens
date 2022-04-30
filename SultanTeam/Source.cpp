#include<stdio.h>
#include<stdlib.h>
#include <time.h>
/*
The function clearBoard() take the matrix board , set all the game board cells to be 'e'
*/
void ClearBoard(char board[][8]);
/*
The function print()  take the matrix board , will print the game board matrix using specific format
*/
void Print(char board[][8]);
/*
The function TestRow()  take the matrix board and the row we want to test
if there is a queen int this row , return 1;
else , return 0
*/
int TestRow(char board[][8],int row);
/*
The function TestColumn()  take the matrix board and the column we want to test
if there is a queen int this column , return 1;
else , return 0
*/
int TestColumn(char board[][8], int column);
/*
The function TestDiagonal()  takes:
	the matrix board,
	and value, if 1: check main diagonal, if 2, check the inverse diagonal
if there is a queen one of the diagonals , return 1;
else , return 0
*/
int TestDiagonal(char board[][8], int r,int c);
/*
The function CanAddQueen()  takes:
	the matrix board,
	and row , column 
if there is a queen row or column or any daigonal  , return 1;
else , return 0
*/
int CanAddQueen(char board[][8], int r, int c);
/*
The function Play()  takes:
	the matrix board
	inside it we will ask user for row and column  he want to enter in
	and test if it is valid or not using CanAddQueen()
	until user win or play again

*/
void Play(char board[][8]);
/*
The function Solve()  takes:
	the matrix board
	the program will suppose numbers randomly represent the row and column and try
	to solve game

*/
void Solve1(char board[][8]);
/*
The function menu()  
	print a home menu
*/
void Menu();
/*
The function getNumberOfQueens()
	print a home menu
*/
int getNumberOfQueens(char board[][8]);
void Solve2(char board[][8]);
int main() {
/*
The game board is 2D array of Characters of size 8×8
 if cell is empty , the board cell will be 'e'
if cell contains Queen , the board cell will be 'q'
*/
	int x;
	char board[8][8];
	ClearBoard(board);

	while (1) {
		Menu();
		scanf_s("%d", &x);
		if (x == 1) {
			ClearBoard(board);
			printf("\x1B[36m");
			printf("CLEARED SUCCESSFULLY :) \n");
			printf("\x1B[37m");
		}
		else if (x == 2) {
			Print(board);
			printf("\x1B[36m");
			printf("*******************************************\n");
			printf("\x1B[37m");
		}
		else if (x == 3) {
			Play(board);
		}
		else if (x == 4)
		{
			Solve1(board);
		}
		else if (x== 5)
		{
			Solve2(board);
		}
		else {
			printf("\n\nBYE BYE\n\n");
			break;
		}
	}
	return 0;
}

void ClearBoard(char board[8][8]) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			 board[i][j]='e';
		}
	}

}
void Print(char board[8][8]) {
	printf("8 * 8 chessboard: \n");
	printf("   -0- -1- -2- -3- -4- -5- -6- -7-\n"); // print column number in the top
	for (int i = 0; i < 8; i++)
	{
		printf("   --- --- --- --- --- --- --- ---\n");
		printf("%d ", i); // print row number at the starting of row
		for (int j = 0; j < 8; j++)
		{
			printf("| ");
			if(board[i][j]=='e')
				printf("  ");
			else {
				printf("\x1B[32m");
				printf("q ");
				printf("\x1B[37m");

			}
		}
		printf("|");
		printf("\n");
	}
	printf("   --- --- --- --- --- --- --- ---\n");

}
int TestRow(char board[][8], int row) 
{
	int found = 0;
	for (int j = 0; j < 8; j++)
	{
		if (board[row][j] == 'q')
		{
			found = 1;
			break;
		}
	}
	return found;

}
int TestColumn(char board[][8], int column) {
	int found = 0;
	for (int i = 0; i < 8; i++)
	{
		if (board[i][column] == 'q')
		{
			found = 1;
			break;
		}
	}
	return found;
}
int TestDiagonal(char board[][8],int r,int c) {
	int found = 0;
	int rows[8] = { -1 };
	int cols[8] = { -1 };
	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 'q') {
				rows[k] = i;
				cols[k] = j;
				k++;
			}
		}
	}

		for (int i = 0; i < k; i++)
		{
			if (rows[i] == r)
				return 1;
		}

		for (int i = 0; i < k; i++)
		{
			if (cols[i] == c)
				return 1;
		}


		for (int i = 0; i < k; i++)
		{
			int diffRows = abs(rows[i] - r);
			int diffCol = abs(cols[i] - c);
			if (diffRows == diffCol)
				return 1;
		}
		return 0;
}
int CanAddQueen(char board[][8], int r, int c) {
	int valid=1;
	if (TestRow(board, r) == 1 || TestColumn(board, c) == 1)
		valid = 0;
	else
	{
		if (TestDiagonal(board,r,c) == 1)
			valid = 0;
	
	}
	
	return valid;
}
void Play(char board[][8]) {
	int row, column;
	time_t t = time(NULL) + 60;
	while (time(NULL) < t)
	{
		
		Print(board);
		printf("Enter row: ");
		scanf_s("%d", &row);
		printf("Enter column: ");
		scanf_s("%d", &column);
		
		if (CanAddQueen(board, row, column))
		{
			board[row][column] = 'q';
			if (getNumberOfQueens(board) == 8)
			{
				printf("\x1B[35m");
				printf(" ******** SOLVED ********** \n");
				printf("\x1B[37m");
				Print(board);
				return;
			}
		}
		else {
			printf("\x1B[31m");
			printf(" ******** INVALID POSITION ********** \n");
			printf("\x1B[37m");
			char ch;
			printf("\x1B[36m");
			printf("Press y to next move or other letter to return : ");
			printf("\x1B[37m");
			scanf_s(" %c",&ch);
			if ((ch == 'y') || (ch == 'Y'))
				continue;
			else
				return;
		}
	}
	printf("\x1B[36m");
	printf("********************\n");
	printf("****  TIME OUT  ****\n");
	printf("********************\n");
	printf("\x1B[37m");
	ClearBoard(board);
}
void Solve1(char board[][8])
{
	srand(time(NULL)); // in header file stdlib.h + generate different values each time
	int Iteration = 0;
	while (1) {
		int row = rand() % 8;
		int column = rand() % 8;
		if (CanAddQueen(board, row, column))
		{
			board[row][column] = 'q';
			Iteration = 0;
			if (getNumberOfQueens(board) == 8)
			{
				printf("\x1B[35m");
				printf(" ******** SOLVED ********** \n");
				printf("\x1B[37m");
				Print(board);
				break;
			}
		}
		Iteration++;
		if (Iteration > 1000000) {
			printf("CANNOT SOLVE IT NOW\n");
			Print(board);
			return;
		}
	
	}
	ClearBoard(board);
}
void Menu() 
{
	printf("\x1B[33m");
	printf("*********** MAIN MENU ***********\n");
	printf("** Press                       **\n");
	printf("** 1. Clear Game Board         **\n");
	printf("** 2. Print Game Board         **\n");
	printf("** 3. Play  Game               **\n");
	printf("** 4. Solve Game Automatically **\n");
	printf("** 5. to print solve           **\n");
	printf("** OtherWise, Exit Game        **\n");
	printf("*********************************\n");
	printf("Your Choise: ");
	printf("\x1B[37m");
}
int getNumberOfQueens(char board[][8]) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 'q')
				count += 1;
		}
	}
	return count;
}
void Solve2(char board[][8])
{
	board[0][3] = { 'q' };
	board[1][1] = { 'q' };
	board[2][6] = { 'q' };
	board[3][2] = { 'q' };
	board[4][5] = { 'q' };
	board[5][7] = { 'q' };
	board[6][4] = { 'q' };
	board[7][0] = { 'q' };
	//return board [8][8];
	Print(board);
	ClearBoard(board);
}
