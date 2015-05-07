/*
Abhishek Jain
sudoku solver
take input from a text file problem.txt
sample input 007356800000279000030040070312487965400603002000000000800030004070864050050020080
get this from http://mypuzzle.org/sudoku --> export the sudoku
check solutions against their solutions
reference doc http://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

const int UNASSIGNED = 0; // blank cells are 0
const int N = 9;          // grid size 9*9
const int BOXSIZE = 3;    // size of a box 3*3

// function to find unassigned location
bool findUnassigned(int grid[N][N],int &row,int &column){  
for (row = 0; row < N; row++)
    for (column = 0; column < N; column++)
        if (grid[row][column] == UNASSIGNED)
            return true;
    return false;
}

//function to check if the number is already used in row
bool usedInRow(int grid[N][N],int row, int num){
for(int column =0; column < N; column++)
    if (grid[row][column] == num)
    return true;  // used in row
return false; // not used
}
//function to check if the number is already used in column
bool usedInColumn(int grid[N][N], int column, int num){
for(int row =0; row < N; row++)
    if (grid[row][column] == num)
    return true; //used
return false; //not used
}
//function to check if the number is already used in box
bool usedInBox(int grid[N][N], int boxStartRow, int boxStartColumn,int num){
for(int row =0; row < BOXSIZE; row++)
    for(int column =0; column < BOXSIZE; column++)
    if (grid[row+boxStartRow][column+boxStartColumn] == num)
    return true;
return false;
}
// function to find conflicts, checks if int num is safe for that location
bool noConflict(int grid[N][N], int row, int column, int num){
return !usedInRow(grid,row,num) && !usedInColumn(grid,column,num) && !usedInBox(grid,row-row%BOXSIZE,column-column%BOXSIZE,num);
}

// function to solve sudoku
bool solveSudoku(int grid[N][N]){
int row, column;
if (!(findUnassigned(grid,row,column))) return true;  // this means no empty cell to fill sudoku solved
for (int num = 1; num <= N; num++){
    if(noConflict(grid,row,column,num)){
        grid[row][column] = num;
        if (solveSudoku(grid)) return true;  // backtracking
        grid[row][column] = UNASSIGNED;  // if conflict, clear the cell
    }
}
return false;
}

class Disp {

public:
 // function to print solved grid
void printGrid(int grid[N][N]){
    cout <<" ------------------------- " << endl;
    for(int row =0; row < N; row++)
        {
        for(int column =0; column < N; column++)
        {
            cout << " " << grid[row][column];
            if (column%3 == 2) cout << " | ";
        }
        cout << endl ;
        if (row%3 == 2) cout <<" ------------------------- " << endl;
        }
    }
};

int main()
{
    Disp disp1;
    int grid[N][N] = {0};
    ifstream file;  // input file
    file.open("problem.txt"); // open
    string str;
    getline(file,str); // copy the line into string str
    char a[81];
    str.copy(a,81); // copy string into char array

int cnt = 0;
        for(int row = 0; row <N;row++)
        {
            for (int column = 0; column < N; column++)
            {
                grid[row][column]= (a[cnt])- '0'; // MAGIC char array to int 2D array
                cnt++;
            }
        }
    cout << "\ninput sudoku\n" << endl;
    disp1.printGrid(grid);

    if(solveSudoku(grid) == true)
    {
        cout << "solution Sudoku\n" << endl;
        disp1.printGrid(grid);
    }
    else
        cout << "something is not quite right" << endl; // in case of no solution
    return 0;
}
