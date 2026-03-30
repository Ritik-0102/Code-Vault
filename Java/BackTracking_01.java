// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

// Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

// Input: n = 4
// Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]

// Input: n = 1
// Output: [["Q"]]

// Time Complexity: O(N!)
// Space Complexity: O(N^2)

import java.util.ArrayList;
import java.util.List;

public class BackTracking_01 {
    public static void Save_Board(List<List<String>> All_Boards,char[][] Board){
        List<String> New_Board = new ArrayList<>();

        for(int i=0;i<Board.length;i++){
            StringBuilder Row = new StringBuilder();
            for(int j=0;j<Board[i].length;j++){
                if(Board[i][j]=='Q'){
                    Row.append('Q');
                }
                else{
                    Row.append('.');
                }
            }
            New_Board.add(Row.toString());
        }

        All_Boards.add(New_Board);
    }

    public static Boolean Queen_is_Safe(char[][] Board , int row ,int col){
        // Vertical
        for(int i=0;i<Board.length;i++){
            if(Board[i][col]=='Q'){
                return false;
            }
        }

        // Horizontal
        for(int i=0;i<Board[0].length;i++){
            if(Board[row][i]=='Q'){
                return false;
            }
        }

        // Upper Left
        int r=row;
        for(int c=col; r>=0 && c>=0 ; r-- , c-- ){
            if(Board[r][c]=='Q'){
                return false;
            }
        }

        // Upper Right
        r=row;
        for(int c=col; r>=0 && c<Board.length; r-- , c++){
            if(Board[r][c]=='Q'){
                return false;
            }
        }

        // Lower Left
        r=row;
        for(int c=col ; r<Board.length && c>=0 ; r++ , c--){
            if(Board[r][c]=='Q'){
                return false;
            }
        }

        // Lower Right
        r=row;
        for(int c=col; c<Board.length && r<Board.length ; r++ , c++){
            if(Board[r][c]=='Q'){
                return false;
            }
        }

        return true;
    }

    public static void helper(List<List<String>> All_Boards,char[][] Board,int col){
        if(col == Board.length){
            Save_Board(All_Boards,Board);
            return;
        }

        for(int row=0;row<Board.length;row++){
            if(Queen_is_Safe(Board,row,col)){
                Board[row][col]='Q';
                helper(All_Boards, Board, col+1);
                Board[row][col]='.';
            }
        }
    }


    public static List<List<String>> solveNQueens(int n){
        List<List<String>> All_Boards=new ArrayList<>();
        char[][] Board = new char[n][n];

        helper(All_Boards,Board,0);

        return All_Boards;
    }


    public static void main(String[] args) {
        int n = 4;
        System.out.println(solveNQueens(n));
    }
}
