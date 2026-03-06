// value = [20,30,40,50,60,70,80,90,100]
// weight = [1,2,3,4,5,6,7,8,9]
// W = 10

#include<iostream>
#include<vector>

using namespace std;

// time complexity = O(2^n)
int knapsack0_1_Recursion(vector<vector<int>>& items,int W,int n){
    if(n==0 || W==0){
        return 0;
    }

    int val = items[n-1][0];
    int wt = items[n-1][1];

    if(wt <= W){
        int include = val + knapsack0_1_Recursion(items,W-wt,n-1);
        int exclude = knapsack0_1_Recursion(items,W,n-1);

        return max(include,exclude);
    }
    else{
        return knapsack0_1_Recursion(items,W,n-1);
    }
}

// Time complexity = O(n*W)
// Space complexity = O(n*W) + O(n) for recursion
int knapsack0_1_Memoization(vector<vector<int>>& items,int W,int n,vector<vector<int>> &dp){
    if(n==0 || W==0){
        return 0;
    }
    
    if(dp[n][W]!=-1){
        return dp[n][W];
    }
    
    int val = items[n-1][0];
    int wt = items[n-1][1];
    
    if(wt <= W){
        int include = val + knapsack0_1_Memoization(items,W-wt,n-1,dp);
        int exclude = knapsack0_1_Memoization(items,W,n-1,dp);
        
        dp[n][W] = max(include,exclude);
        return dp[n][W];
    }
    else{
        dp[n][W] = knapsack0_1_Memoization(items,W,n-1,dp);
        return dp[n][W];
    }
}

// Time complexity = O(n*W)
// Space complexity = O(n*W)
int knapsack0_1_Tabulation(vector<vector<int>>& items,int W,int n){
    vector<vector<int>> dp(n+1,vector<int>(W+1,0));

    for(int i=1;i<=n;i++){

        int val = items[i-1][0];
        int wt = items[i-1][1];

        for(int j=1;j<=W;j++){
            if(wt <= j){
                // Max of including the current item vs excluding it
                dp[i][j] = max(dp[i-1][j-wt]+val,dp[i-1][j]);
            }
            else{
                // If weight is more than current capacity, exclude it
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp[n][W];
}

int main(){
    vector<vector<int>> items = {{20,1},{30,2},{40,3},{50,4},{60,5},{70,6},{80,7},{100,9}};
    int W = 10;
    int n = items.size();

    cout << knapsack0_1_Recursion(items,W,n) << endl;

    vector<vector<int>> dp(n+1,vector<int>(W+1,-1));
    cout << knapsack0_1_Memoization(items,W,n,dp) << endl;

    cout << knapsack0_1_Tabulation(items,W,n) << endl;

    return 0;
}