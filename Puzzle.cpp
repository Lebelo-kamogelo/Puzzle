/**********************************************************
*  The 8-puzzle is a sliding puzzle that is played on a   *
*  3-by-3 grid with 8 square tiles labeled 1 through 8,   *
*  plus a blank square. The goal is to rearrange          *
*  the tiles so that they are in row-major order,         *
*  using as few moves as possible.                        *
*  You are permitted to slide tiles either horizontally or*
*  vertically into the blank square                       *
***********************************************************/

#include <iostream>

using namespace std;

int initial[3][3] = { //Initial State
	{8,6,7}, 
	{2,5,4}, 
	{3,0,1}
};

int goal[3][3] = { //Goal State
	{1,2,3}, 
	{4,5,6}, 
	{7,8,0} 
};

const int Max = 50; 

int moves[Max];

int best_move[Max]; //Stores the numbers that was visited during solving

int best_depth = Max; //Store the length of the shortest iteration

int Solved() {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (initial[i][j] != goal[i][j]) {
				return 0; //Return 0, if the puzzle isn't solved
			}
		}
	}
	return 1; //Return 1 if the puzzled is solved
}

void search(int row, int col, int depth, int one, int two) {

	if (depth >= best_depth) return; //Check the short path

	if (depth != 0)moves[depth - 1] = initial[one][two];

	if (Solved()) { //Check if the puzzle is solved

		best_depth = depth;

		for (int i = 0; i < depth; i++)
		{
			best_move[i] = moves[i]; //Store the shortest path
		}

		return;
	}

	int row1, col1;
	int row2, col2;
	int row3, col3;
	int row4, col4;

	//Directions
	row1 = row + 1; col1 = col;
	row2 = row - 1; col2 = col;
	row3 = row; col3 = col + 1;
	row4 = row; col4 = col - 1;

	if (row1 == one && col1 == two) row1 = col1 = -1;
	if (row2 == one && col2 == two) row2 = col2 = -1;
	if (row3 == one && col3 == two) row3 = col3 = -1;
	if (row4 == one && col4 == two) row4 = col4 = -1;

	//Find the best routine around the puzzle borad
	if (row1 >= 0 && col1 >= 0 && row1 < 3 && col1 < 3) {
		initial[row][col] = initial[row1][col1]; initial[row1][col1] = 0;
		search(row1, col1, depth + 1, row, col);
		initial[row1][col1] = initial[row][col]; initial[row][col] = 0;
	}
	if (row2 >= 0 && col2 >= 0 && row2 < 3 && col2 < 3) {
		initial[row][col] = initial[row2][col2]; initial[row2][col2] = 0;
		search(row2, col2, depth + 1, row, col);
		initial[row2][col2] = initial[row][col]; initial[row][col] = 0;
	}
	if (row3 >= 0 && col3 >= 0 && row3 < 3 && col3 < 3) {
		initial[row][col] = initial[row3][col3]; initial[row3][col3] = 0;
		search(row3, col3, depth + 1, row, col);
		initial[row3][col3] = initial[row][col]; initial[row][col] = 0;
	}
	if (row4 >= 0 && col4 >= 0 && row4 < 3 && col4 < 3) {
		initial[row][col] = initial[row4][col4]; initial[row4][col4] = 0;
		search(row4, col4, depth + 1, row, col);
		initial[row4][col4] = initial[row][col]; initial[row][col] = 0;
	}



}

int main() {

	int row, col;
	
	//Find the coordinates
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++){
			if (initial[i][j] == 0) {
				row = i;
				col = j;
				break;
			}
		}
	}

	search(row, col, 0, -1, -1);

	cout << "Path :" << endl;

	for (size_t i = 0; i < best_depth; i++) //Output the path
	{
		cout << "0 <-> " << best_move[i] << endl;
	}

	cout << "\nInitial State" << endl;
	for (int i = 0; i < 3; i++) //Output the initial State
	{
		for (int j = 0; j < 3; j++)
		{
			cout << initial[i][j] << " ";
		}cout << endl;
	}

	for (int i = 0; i < best_depth; i++)
	{
		int temp = best_move[i]; //Temporary variable used for swapping
		cout << "\nIteration " << i + 1 << endl;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (initial[x][y] == 0) { 
					initial[x][y] = 10; // "10" temporary number used to swap the number
				}
				if (initial[x][y] == temp) {
					initial[x][y] = 0;
				}
				if (initial[x][y] == 10) {
					initial[x][y] = temp;
				}
			}
		}
		for (int x = 0; x < 3; x++) //Output the puzzle towards the goal state
		{
			for (int y = 0; y < 3; y++)
			{
				cout << initial[x][y] << " ";
			}cout << endl;
		}

	}
	cout << "\nDone" << endl;


	return 0;
}