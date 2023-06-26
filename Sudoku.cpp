#include "Sudoku.h"

Sudoku::Sudoku()
{
	srand(time(0));
	this->grid.resize(9, vector<int>(9));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			this->grid[i][j] = UNASSIGNED;
		}
	}
}

pair<int, int> Sudoku::FindUnassignedLocation(int grid[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (grid[row][col] == UNASSIGNED)
				return { row, col };
		}
	}
	return { -1, -1 };
}

bool Sudoku::IsSafe(int row, int col, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (this->grid[row][i] == num)
			return false;
	}

	for (int i = 0; i < 9; i++)
	{
		if (this->grid[i][col] == num)
			return false;
	}

	int boxRow = row - row % 3;
	int boxCol = col - col % 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (this->grid[boxRow + i][boxCol + j] == num)
				return false;
		}
	}

	return true;
}


void swapCol(int m, int n, vector<vector<int>>& grid)
{
	vector<int>temp(grid.size(), UNASSIGNED);
	for (int i = 0; i < grid.size(); i++)
	{
		temp[i] = grid[i][m];
		grid[i][m] = grid[i][n];
		grid[i][n] = temp[i];
	}
}

void Sudoku::create()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int n = rand() % 9 + 1;
			while (this->IsSafe(i, j, n) != true)
				n = rand() % 9 + 1;
			this->grid[i][j] = n;
		}
	}

	int choice[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
	for (int j = 0; j < 3; j++)
	{
		int i = rand() % 9;
		grid[choice[i][0]].swap(grid[choice[i][1]]);
		swapCol(choice[i][0], choice[i][1], grid);
	}
}

void Sudoku::printGrid()
{
	for (int i = 0; i < 9; i++)
	{
		if(i % 3 == 0 && i != 0)
			cout << "-------------------" << endl;
		for (int j = 0; j < 9; j++)
		{
			if (j % 3 == 0)
				cout << '|';
			cout << this->grid[i][j];
			if (j % 3 != 2)
				cout << ' ';
		}
		cout << '|' << endl;
	}
}
