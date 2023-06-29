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
		if (argc == 3) {
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
		else if (argc == 5 && strcmp(argv[3], "-m") == 0) {
			int dif = atoi(argv[4]);
			int num = atoi(argv[2]);
			FILE* fp;
			fp = fopen("./game.txt", "w+");
			while (num > 0) {
				sudoku.create();
				sudoku.genPuzzleWithDifficulty(dif);
				sudoku.printFormattedGrid(fp);
				num--;
			}
			fclose(fp);
		}
		else if (argc == 5 && strcmp(argv[3], "-r") == 0) {
			char begin[2];
			char end[2];
			begin[0] = argv[4][0];
			begin[1] = argv[4][1];
			end[0] = argv[4][3];
			end[1] = argv[4][4];
			int rbegin = atoi(begin);
			int rend = atoi(end);

			int num = atoi(argv[2]);
			FILE* fp;
			fp = fopen("./game.txt", "w+");
			while (num > 0) {
				sudoku.create();
				int r = rbegin + rand() % (rend - rbegin);
				sudoku.genPuzzleWithNum(r);
				sudoku.printFormattedGrid(fp);
				num--;
			}
			fclose(fp);
			

		}
		else if (argc == 4 && strcmp(argv[3], "-u") == 0) {
			int num = atoi(argv[2]);
			FILE* fp;
			fp = fopen("./game.txt", "w+");
			while (num > 0) {
				sudoku.create();
				sudoku.genUniquePuzzle();
				sudoku.printFormattedGrid(fp);
				num--;
			}
			fclose(fp);
		}
		
	}
	else {
		cout << "Arguments ERROR!" << endl;
		return 0;
	}

	return 0;
}