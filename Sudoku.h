#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>

#define UNASSIGNED 0


using namespace std;

class Sudoku
{
private:
	int grid[9][9];
	int solnGrid[9][9];
	int guessNum[9];
	int gridPos[81];

public:
	Sudoku();
	pair<int, int> FindUnassignedLocation();
	bool IsSafe(int row, int col, int num);
	void create();
	bool solveGrid();
	void countSln(int& number);
	void genUniquePuzzle();
	void genPuzzleWithDifficulty(int dif);
	void genPuzzleWithNum(int num);
	void printFormattedGrid(FILE* fp);
	void printFormattedSolnGrid(FILE* fp);
	void readPuzzle(ifstream &infile);
};