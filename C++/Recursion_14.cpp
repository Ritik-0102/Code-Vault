// Count Unique Paths in a Grid

// In this code we are trying to calculate no. of possible paths from one position to the last position in a GRID, And we can only move in right or downward direction

#include<iostream>
#include<vector>

using namespace std;

// 1st Approach

// Time Complexity : O(2^(m+n))
// This is a worst Time Complexity

int grid_path(int m,int n){
    if(m==1 && n==1){
        return 1;
    }
    if(m<1 || n<1){
        return 0;
    }
    
    return grid_path(m-1,n) + grid_path(m,n-1);
}

// 2nd Approach - Dynamic Programming (Tabulation)

// This is the best approach to do this problem

int Grid_path(int m, int n){
    // Standard C++ way to create a dynamic 2D array initialized with 0
    vector<vector<int>> arr(m, vector<int>(n, 0)); 
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(i == 0 || j == 0){
                // The first row and first column can only be reached in 1 way (straight line)
                arr[i][j] = 1; 
            }
            else{
                // Current cell is the sum of the cell above it and the cell to its left
                arr[i][j] = arr[i-1][j] + arr[i][j-1];
            }
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return arr[m-1][n-1];
}

int main(){
    cout << "Total paths: " << grid_path(4, 6) << endl;
    cout << "Total paths: " << Grid_path(4, 6) << endl;

    return 0;
}