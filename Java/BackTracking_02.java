// Sudoku Solver

public class BackTracking_02 {
    public static boolean isSafe(int[][] board, int row, int col, int num) {
        // Check if 'num' is not in the given row and column
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num || board[i][col] == num) {
                return false;
            }
        }

        // Check if 'num' is not in the 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    public static boolean solveSudoku(int[][] board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) { // Find an empty cell
                    for (int num = 1; num <= 9; num++) {
                        if (isSafe(board, row, col, num)) {
                            board[row][col] = num; // Place the number

                            if (solveSudoku(board)) {
                                return true; // Recur to place the next number
                            }

                            board[row][col] = 0; // Backtrack
                        }
                    }
                    return false; // Trigger backtracking
                }
            }
        }
        return true; // Sudoku solved
    }

    public static void printBoard(int[][] board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] board = {
                {3, 0, 6, 5, 0, 8, 4, 0, 0},
                {5, 2, 0, 0, 0, 0, 0, 0, 0},
                {0, 8, 7, 0, 0, 0, 0, 3, 1},
                {0, 0, 3, 0, 1, 0, 0, 8, 0},
                {9, 0, 0, 8, 6, 3, 0, 0, 5},
                {0, 5, 0, 0, 9, 0, 6, 0, 0},
                {1, 3, 0, 0, 0, 0, 2, 5, 0},
                {0, 0, 0, 0, 0, 0, 0, 7 ,4},
                {0 ,0 ,5 ,2 ,0 ,6 ,3 ,0 ,9}
        };

        if (solveSudoku(board)) {
            printBoard(board);
        } else {
            System.out.println("No solution exists");
        }
    }
}
