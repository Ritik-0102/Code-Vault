#include<iostream>
#include<vector>

using namespace std;

int solve(vector<vector<int>>& grid ,int i, int j){
    if(i<0 || j<0 || i>=grid.size() || j>=grid[i].size() ){
        return 0;
    }

    grid[i][j]=0;
    int l=solve(grid,i,j-1);
    int r=solve(grid,i,j+1);
    int u=solve(grid,i-1,j);
    int d=solve(grid,i+1,j);

    return l+r+u+d+1;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[i].size();j++){
                int max=INT_FAST64_MIN;
                int sol=solve
            }
        }
    }