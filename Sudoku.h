#pragma once
#include <iostream>
#include <vector>

#define UNASSIGNED 0

using namespace std;

class Sudoku
{
private:
	vector<vector<int>> grid;
	int solvedGrid[9][9];
	int difficulty;

public:
	Sudoku();
	pair<int, int> FindUnassignedLocation(int grid[9][9]);
	bool IsSafe(int row, int col, int num);
	void create();
	void printGrid();
};