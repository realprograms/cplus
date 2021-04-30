//
// Problem: Place N chees queens on N x N chessboard so that no two queens attack each other.
//          in another word, no two queens are on the same row, the same column or the two diagonals
//
// backtracking algorithm: strats from the leftmost
// state space tree:

#include <iostream>
#include <vector>

using namespace std;

// since we start from left, nothing on the columns at the right
bool  isQueenSafe(vector<vector<int>>& chessboard, int row, int col) 
{
    int N = chessboard[0].size();
    int i, j;

    // check the row on the left
    for (j = 0; j < col; ++j) {
        if ( chessboard[row][j] ) {
            // cout << "Not Safe: " << j << "x" << row << endl;
            return false;
        }
    }

    // check the upper left diagonal
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if ( chessboard[i][j] ) {
            // cout << "Not Safe: " << i << "x" << j << endl;
            return false;
        }
    }

    // check the lower left diagonal
    for (i = row + 1, j = col - 1; i < N && j >= 0; ++i, --j ) {
        if ( chessboard[i][j] ) {
            // cout << "Not Safe: " << i << "x" << j << endl;
            return false;
        }
    }
    // cout << "Safe: " << row << "x" << col << endl;
    return true;
}

// start placing one Queen from the leftmost column (col = 0)
bool placeQueen(vector<vector<int>>& chessboard, int row, int col, vector<vector<vector<int>>>& sQ) 
{
    int N = chessboard[0].size();
    
    if ( col == N) {
        // cout << "got it: " << col << endl;
        return true;
    }
    else
    {
        // cout << "Place Queen on column: " << col << " " << endl;
    }

    for (int i = row; i < N; ++i) {
        if ( isQueenSafe(chessboard, i, col) ) {
            chessboard[i][col] = 1;
            // cout << "set: " << i << "-" << col << " " << endl;

            if ( placeQueen(chessboard, 0, col+1, sQ) ) {
                sQ.push_back(chessboard);
                // return true;
            }

            chessboard[i][col] = 0;  // backtracking
            // cout << "clr: " << i << "-" << col << endl;
        }
    }
    return false;
}
void clearNQueen(vector<vector<int>>& matrix) 
{
    int N = matrix.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = 0;
        }
    }
}

template <class T>
void printNQueen(const vector<vector<T>>& matrix) 
{
    cout << "-------" << " Print Queen " << "--------" << endl;
    for (vector<T> row: matrix) { 
		for (T val: row) {
			cout << val << " ";
		}
		cout << endl;
	}
}

vector<vector<vector<int>>> solveNQueen(int N) 
{
    vector<vector<vector<int>>> solutionQ;
    vector<vector<int>> chessboard(N, vector<int>(N, 0));
    placeQueen(chessboard, 0, 0, solutionQ);
    return solutionQ;
}

// 5-Queens: 10 Solutions
// [["Q....","..Q..","....Q",".Q...","...Q."],
//  ["Q....","...Q.",".Q...","....Q","..Q.."],
//  [".Q...","...Q.","Q....","..Q..","....Q"],
//  [".Q...","....Q","..Q..","Q....","...Q."],
//  ["..Q..","Q....","...Q.",".Q...","....Q"],
//  ["..Q..","....Q",".Q...","...Q.","Q...."],
//  ["...Q.","Q....","..Q..","....Q",".Q..."],
//  ["...Q.",".Q...","....Q","..Q..","Q...."],
//  ["....Q",".Q...","...Q.","Q....","..Q.."],
//  ["....Q","..Q..","Q....","...Q.",".Q..."]]

// driver program to test above function 
int main(int argc, char *argv[])
{ 
    int N = 5;
    if (argc > 1) {
        if ((N = atoi(argv[1])) < 0)
            return -1;
    }
    if (N > 9) {
        cout << "this may take longer time ..." << endl;
    }
    vector<vector<vector<int>>> sQ = solveNQueen(N);
    for (int i = 0; i < sQ.size(); ++i) {
        cout << "solution " << i + 1 << ": " << endl;
        for (int j = 0; j < sQ[i].size(); ++j) {
            for (int k = 0; k < sQ[i][j].size(); ++k) {
                cout << sQ[i][j][k] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
    return 0; 
} 