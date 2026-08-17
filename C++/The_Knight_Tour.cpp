// The Knight Tour Problem

#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    if (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == -1) {
        return true;
    }
    return false;
}

bool helper(vector<vector<int>>& board, const vector<int>& moveX, const vector<int>& moveY, int row, int col, int move) {
    int n = board.size();
    
    // Safety check first
    if (!isSafe(board, row, col, n)) {
        return false;
    }
    
    // Mark the current cell with the current move number
    board[row][col] = move;
    
    // Base case : If we just placed the final move (n*n - 1), we are done.
    if (move == n * n - 1) {
        return true;
    }
    
    for (int i = 0; i < 8; i++) {
        int nextMoveX = row + moveX[i];
        int nextMoveY = col + moveY[i];
        
        if (helper(board, moveX, moveY, nextMoveX, nextMoveY, move + 1)) {
            return true;
        }
    }
    
    // Backtrack
    board[row][col] = -1;
    
    // Return false if all 8 paths from this square fail
    return false;
}

vector<vector<int>> knightTour(int n) {
    // Initialize the board of n x n with -1
    vector<vector<int>> board(n, vector<int>(n, -1));
    
    // These are combination of X & Y 
    vector<int> moveX = {2, 2, -2, -2, 1, 1, -1, -1};
    vector<int> moveY = {1, -1, -1, 1, 2, -2, -2, 2};
    
    // Start the recursive helper. 
    // If it returns true, the board is populated correctly.
    if (helper(board, moveX, moveY, 0, 0, 0)) {
        return board;
    }
    
    // If it returns false (no solution exists, like for N=2) , return an empty vector
    return {}; 
}

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> board = knightTour(n);
    
    if (board.empty()) {
        cout << "No solution exists" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}