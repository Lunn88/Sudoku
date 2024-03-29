#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Sudoku.h"

int genRandNum(int maxLimit)
{
	return rand() % maxLimit;
}

Sudoku::Sudoku()
{
	for (int i = 0; i < 81; i++)
	{
		this->gridPos[i] = i;
	}

	random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);

	for (int i = 0; i < 9; i++)
	{
		this->guessNum[i] = i + 1;
	}

	random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

	srand(time(0));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			this->grid[i][j] = UNASSIGNED;
		}
	}
}

pair<int, int> Sudoku::FindUnassignedLocation()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (this->grid[row][col] == UNASSIGNED)
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

void Sudoku::create()
{
	//填入对角线的粗线宫
	for (int idx = 0; idx < 3; idx++) {
		int start = idx * 3;
		random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				this->grid[start + i][start + j] = guessNum[i * 3 + j];
			}
		}
	}

	this->solveGrid();//补全

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			this->solnGrid[i][j] = this->grid[i][j];
		}
	}
}

bool Sudoku::solveGrid()
{
	pair<int, int> pos = this->FindUnassignedLocation();
	int row = pos.first;
	int col = pos.second;
	if (row == -1 && col == -1)
		return true;


	for (int num = 0; num < 9; num++)
	{
		// 尝试填入空缺的值
		if (this->IsSafe(row, col, this->guessNum[num]))
		{
			// 填入
			this->grid[row][col] = this->guessNum[num];

			// 判断填入后是否正确
			if (solveGrid())
				return true;

			// 不正确则不填入
			this->grid[row][col] = UNASSIGNED;
		}
	}

	return false;
}

void Sudoku::countSln(int& number)
{
	pair<int, int> pos = this->FindUnassignedLocation();
	int row = pos.first;
	int col = pos.second;
	if (row == -1 && col == -1) {
		number++;
		return;
	}

	for (int i = 0; i < 9 && number < 2; i++)
	{
		if (this->IsSafe(row, col, this->guessNum[i]))
		{
			this->grid[row][col] = this->guessNum[i];
			countSln(number);
		}

		this->grid[row][col] = UNASSIGNED;
	}
}

void Sudoku::genUniquePuzzle()
{
	for (int i = 0; i < 81; i++)
	{
		int x = (this->gridPos[i]) / 9;
		int y = (this->gridPos[i]) % 9;
		int temp = this->grid[x][y];
		this->grid[x][y] = UNASSIGNED;

		// 限制唯一解
		int check = 0;
		countSln(check);
		if (check != 1)
		{
			this->grid[x][y] = temp;
		}
	}
}

void Sudoku::genPuzzleWithNum(int num)
{
	for (int i = 0; i < num; i++)
	{
		int x = (this->gridPos[i]) / 9;
		int y = (this->gridPos[i]) % 9;
		this->grid[x][y] = UNASSIGNED;
	}
}

void Sudoku::genPuzzleWithDifficulty(int dif)
{
	int r = rand() % 10;
	this->genPuzzleWithNum(10 + dif * 10 + r);
}

void Sudoku::printFormattedGrid(FILE* fp)
{
	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0 && i != 0)
			fprintf(fp, "-------------------\n");
		for (int j = 0; j < 9; j++)
		{
			if (j % 3 == 0)
				fprintf(fp, "|");

			if (this->grid[i][j] != 0)
				fprintf(fp, "%d", this->grid[i][j]);
			else
				fprintf(fp, "$");
			
			if (j % 3 != 2)
				fprintf(fp, " ");
		}
		fprintf(fp, "|\n");
	}
	fprintf(fp, "-\n");
}

void Sudoku::printFormattedSolnGrid(FILE* fp)
{
	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0 && i != 0)
			fprintf(fp, "-------------------\n");
		for (int j = 0; j < 9; j++)
		{
			if (j % 3 == 0)
				fprintf(fp, "|");
			fprintf(fp, "%d", this->solnGrid[i][j]);
			if (j % 3 != 2)
				fprintf(fp, " ");
		}
		fprintf(fp, "|\n");
	}
	fprintf(fp, "-\n");
}

void Sudoku::readPuzzle(ifstream &infile)
{
	char c;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9;)
		{
			c = infile.get();
			if (c != ' ' && c != '\n' && c != '|' && c != '-')
			{
				if (c != '$')
				{
					int tmp = c - '0';
					this->grid[i][j] = tmp;
				}
				else
					this->grid[i][j] = 0;
				j++;
			}
			
		}
	}
}