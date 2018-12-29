#pragma once
#ifndef _SUDUKU_H
#define _SUDUKU_H
void createshifttable();
void showsudoku(char sudoku[9][9]);
void readsudoku(string path, char sudoku[][9][9], int& n);
void savesudoku(string path, char sudoku[9][9], int access = ios::app);
void getsudokuFinality2(string path, int number);
void getsudokuFinality(string path, int number);
void findvalid(char sudoku[][9], int row, int col, bool valid[10]);
bool checksudoku(char sudoku[][9]);
bool dosolve(char sudoku[][9]);
void solvesudoku(string path, string outpath);

#endif // !_SUDUKU_H
