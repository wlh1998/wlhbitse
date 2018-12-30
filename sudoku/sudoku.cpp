// sudoku.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "sudoku.h"
using namespace std;

//学号1120161759，（5+9）%9 + 1 = 6
//生成n个数独，保存至path中。
int shifttable[36][9];
void createshifttable() {
	int shift[9] = { 0,3,6,1,4,7,2,5,8 };
	int n = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i)
		{
			next_permutation(shift + 3, shift + 6);
			shift[6] = 2;
			shift[7] = 5;
			shift[8] = 8;
		}
		for (int j = 0; j < 6; j++)
		{
			if (j)
			{
				next_permutation(shift + 6, shift + 9);
			}
			for (int k = 0; k < 9; k++)
			{
				shifttable[n][k] = shift[k];
			}
			n++;
		}
	}
}
void showsudoku(char sudoku[9][9]) {

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << sudoku[i][j] << " ";
		}
		cout << sudoku[i][8];
		cout << endl;
	}
}

void readsudoku(string path, char sudoku[][9][9],int& n) {
	ifstream infile;
	infile.open(path);
	if (!infile) {
		return;
	}
	n = 0;
	while (!infile.eof())
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				infile >> sudoku[n][i][j];
			}
		}
		n++;
	}

}
//
void savesudoku(string path,char sudoku[9][9],int access) {
	ofstream outfile;
	outfile.open(path,access);
	if (!outfile) {
		return;
	}
	if (access == ios::app)
	{
		outfile << endl;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			outfile << sudoku[i][j]<< " ";
		}
		outfile << sudoku[i][8];
		if (i != 8)
		{
			outfile << endl;
		}
	}
	outfile.close();
}

void getsudokuFinality2(string path, int number) {
	int n = number;
	char sudoku[36][10][18];
	char outchararray[36 * (9 * 18 + 1)];
	createshifttable();
	FILE * file = fopen(path.c_str(), "w");
	for (int k = 0; k < 36; k++)
	{
		outchararray[k * 163 + 162] = '\n';
//		sudoku[k][9][0] = '\n';
//		sudoku[k][9][1] = '\0';
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				outchararray[k * 163 + i * 18 + j * 2 + 1] = ' ';
//				sudoku[k][i][j * 2 + 1] = ' ';
			}
			outchararray[k * 163 + i * 18 + 17] = '\n';
//			sudoku[k][i][17] = '\n';
			
		}
	}

			char line[10] = "612345789";
			for (int k = 0; k < 40320 && n; k++)
			{
				if (k)
				{
					next_permutation(line + 1, line + 9);
				}
				int (*shift) = shifttable[0];
				int i;
				int index = 0;
				for (i = 0; i < 36 && n; i++)
				{
					shift = shift + 9;
					for (int r = 0; r < 9; r++)
					{
						for (int c = 0; c < 9; c++)
						{
						//	sudoku[i][r][((c + shift[r]) % 9) * 2] = line[c];
							outchararray[i*163+r*18+ ((c + shift[r]) % 9) * 2] = line[c];
						}
					}
					n--;
				}
				if (n)
				{
					fwrite(outchararray,sizeof(char),i*(9*18+1), file);
				}
				else
				{
					fwrite(outchararray, sizeof(char), i*(9 * 18 + 1)-1, file);
				}
			}
	fclose(file);
}
void getsudokuFinality(string path, int number) {
	int n = number;
	char sudoku[9][21];
	
	FILE * file = fopen(path.c_str(),"w");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sudoku[i][j * 2 + 1] = ' ';
		}
		sudoku[i][17] = '\n';
		sudoku[i][18] = '\0';
	}
	int shift[9] = { 0,3,6,1,4,7,2,5,8 };
	for (int i = 0; i < 6 && n; i++)
	{
		if (i)
		{
			next_permutation(shift + 3, shift + 6);
			shift[6] = 2;
			shift[7] = 5;
			shift[8] = 8;
		}
		for (int j = 0; j < 6 && n; j++)
		{
			printf("%d\n", number - n);
			if (j)
			{
				next_permutation(shift + 6, shift + 9);
			}
			char line[10] = "678912345";
			for (int k = 0; k < 40320 && n; k++)
			{
				
				if (k)
				{
					next_permutation(line + 1, line + 9);
				}
				for (int r = 0; r < 9; r++)
				{
					for (int c = 0; c < 9; c++)
					{
						sudoku[r][((c + shift[r]) % 9)*2] = line[c];
					}
					fputs(sudoku[r], file);
				}
				n--;
			}
		}
	}
	fclose(file);
}
void findvalid(char sudoku[][9], int row, int col, bool valid[10]) {
	for (int i = 1; i < 10; i++)
	{
		valid[i] = true;
	}
	for (int i = 0; i < 9; i++)
	{
		valid[sudoku[row][i] - '0'] = false;
		valid[sudoku[i][col] - '0'] = false;
	}
	int d[] = {0,1,2,-1,0,1,-2,-1,0};
	int rowflag = row % 3;
	int colflag = col % 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			valid[sudoku[row + d[rowflag * 3 + i]][col + d[colflag * 3 + i]]] = false;
		}
	}
}
bool checksudoku(char sudoku[][9]) {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{

		}
	}
	return true;
}
bool dosolve(char sudoku[][9]) {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == '0')
			{
				bool valid[10];
				findvalid(sudoku,i,j,valid);
				for (int k = 1; k < 10; k++)
				{
					if (valid[k])
					{
						sudoku[i][j] = k+'0';
						if (dosolve(sudoku)) {
							return true;
						}
					}
				}
				sudoku[i][j] = '0';
				return false;
			}
		}
	}
	return true;
}
void solvesudoku(string path,string outpath) {
	char outarray[9 * 18 + 1];
	char inarray[20][18];
	char sudoku[9][9];
	FILE * file = fopen(path.c_str(), "r");
	FILE * fileout = fopen(outpath.c_str(), "w");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			outarray[i * 18 + j * 2 + 1] = ' ';
		}
		outarray[i*18 + 17] = '\n';
	}
	outarray[9 * 18] = '\n';
	int index = 0;
	while (fgets(inarray[0], 20, file)!=NULL) {
		if (index != 0)
		{
			fwrite(outarray, sizeof(char), 9 * 18 + 1, fileout);
		}
		index++;
		if (inarray[0][0] == '\n') {
			continue;
		}
		for (int i = 0; i < 9; i++)
		{
			sudoku[0][i] = inarray[0][i * 2];
		}
		for (int i = 1; i < 9; i++)
		{
			fgets(inarray[i], 20, file);
			for (int j = 0; j < 9; j++)
			{
				sudoku[i][j] = inarray[i][j * 2];
			}
		}
		dosolve(sudoku);

		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				outarray[r*18 + c * 2] = sudoku[r][c];
			}
		}
	}

	fwrite(outarray, sizeof(char), 9 * 18, fileout);
	fclose(file);
	fclose(fileout);
}
void test() {

	char sudoku[9][9];
	char sudokus[100][9][9];
	string path = "sudoku.txt";
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = j + 1;
		}
	}
	savesudoku(path, sudoku);
	savesudoku(path, sudoku, ios::app);

	int n;
	readsudoku(path, sudokus, n);
	for (size_t i = 0; i < n; i++)
	{
		showsudoku(sudokus[i]);
	}

}
void test2() {
	int a[9] = { 1,2,3,4,5,6,7,8,9 };
//	char sudoku[9][9];
	getsudokuFinality("a.txt", 100);

//	showsudoku(sudoku);
}
int commandprocess(int argc,char ** argv) {

	if (!strcmp(argv[1], "-c")) {
		int num;
		sscanf(argv[2], "%d", &num);
		if (num < 0 || num > 1000000) {
			return 1;
		}
		getsudokuFinality2("sudoku.txt", num);
	}
	if (!strcmp(argv[1], "-s")) {
		string path = argv[2];
		solvesudoku(path, "sudoku.txt");
	}
	return 0;
}
int main(int argc, char **argv)
{
	commandprocess(argc, argv);
	return 0;
}
