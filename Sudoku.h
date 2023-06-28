#pragma once
#include <iostream>

#define UNASSIGNED 0

using namespace std;

class Sudoku
{
private:
	int grid[9][9];
	int solnGrid[9][9];
	int guessNum[9];
	int gridPos[81];
	int difficulty;

public:
	Sudoku();
	pair<int, int> FindUnassignedLocation();
	bool IsSafe(int row, int col, int num);
	void create();
	bool solveGrid();
	void countSln(int& number);
	void genPuzzle();
	void printSolution();
	void printPuzzle();
	void readPuzzle();
};