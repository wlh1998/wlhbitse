#pragma once
#ifndef _SUDUKU_H
#define _SUDUKU_H
void createshifttable();
void showsudoku(char sudoku[9][9]);
void readsudoku(std::string path, char sudoku[][9][9], int& n);
void savesudoku(std::string path, char sudoku[9][9], int access = std::ios::app);
void getsudokuFinality2(std::string path, int number);
void getsudokuFinality(std::string path, int number);
void findvalid(char sudoku[][9], int row, int col, bool valid[10]);
bool checksudoku(char sudoku[][9]);
bool dosolve(char sudoku[][9]);
void solvesudoku(std::string path, std::string outpath);
int commandprocess(int argc, char ** argv);
#endif // !_SUDUKU_H
