#include"Sudoku.h"

int main(int argc, char** argv) {
	Sudoku sudoku;

	if (strcmp(argv[1], "-c") == 0) {
		int num = atoi(argv[2]);
		FILE* fp;
		fp = fopen("./solved.txt", "w+");
		while (num > 0) {
			sudoku.create();
			sudoku.printFormattedSolnGrid(fp);
			num--;
		}
		fclose(fp);
	}

	else if (strcmp(argv[1], "-s") == 0) {
		char path[100] = "./";
		strcat(path, argv[2]);
		ifstream infile;
		infile.open(path, ios::in);

		FILE* fp;
		fp = fopen("./sudoku.txt", "w+");
		while (infile.peek() != EOF)
		{
			sudoku.readPuzzle(infile);
			infile.get(); infile.get(); infile.get(); infile.get();
			sudoku.solveGrid();
			sudoku.printFormattedGrid(fp);
		}
		fclose(fp);
	}

	else if (strcmp(argv[1], "-n") == 0) {
		int num = atoi(argv[2]);
		FILE* fp;
		fp = fopen("./game.txt", "w+");
		while (num > 0) {
			sudoku.create();
			sudoku.genPuzzleWithNum(30);
			sudoku.printFormattedGrid(fp);
			num--;
		}
		fclose(fp);
	}

	return 0;
}