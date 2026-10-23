// https://www.naukri.com/code360/problems/frog-jump_3621012

// Problem statement
// There is a frog on the '1st' step of an 'N' stairs long staircase. The frog wants to reach the 'Nth' stair. 'HEIGHT[i]' is the height of the '(i+1)th' stair.If Frog jumps from 'ith' to 'jth' stair, the energy lost in the jump is given by absolute value of ( HEIGHT[i-1] - HEIGHT[j-1] ). If the Frog is on 'ith' staircase, he can jump either to '(i+1)th' stair or to '(i+2)th' stair. Your task is to find the minimum total energy used by the frog to reach from '1st' stair to 'Nth' stair.


#include<iostream>
#include<vector>

using namespace std;

int frogJump_Memoization(int n, vector<int> &height,vector<int>& dp){
    if(n == 0){
        dp[0] = 0;
        return 0;
    }

    if(dp[n] != -1){
        return dp[n];
    }

    int jumpOne = frogJump_Memoization(n-1, height, dp) + abs(height[n] - height[n-1]);
    int jumpTwo = INT_MAX;
    if(n > 1){
        jumpTwo = frogJump_Memoization(n-2, height, dp) + abs(height[n] - height[n-2]);
    }

    dp[n] = min(jumpOne, jumpTwo);

    return dp[n];
}


int frogJump_Tabulation(int n, vector<int> &height){
    if(n == 0){
        return 0;
    }

    vector<int> dp(n, 0);
    dp[0] = 0;
    dp[1] = abs(height[1] - height[0]);
    
    for(int i = 2; i < n; i++){
        int jumpOne = dp[i-1] + abs(height[i] - height[i-1]);
        int jumpTwo = dp[i-2] + abs(height[i] - height[i-2]);
        dp[i] = min(jumpOne, jumpTwo);
    }
    
    return dp[n-1];
}

int main(){
    int n = 4;
    vector<int> height = {10, 20, 30, 10};

    vector<int> dp(n, -1);

    cout << frogJump_Memoization(n-1, height, dp) << endl;

    cout << frogJump_Tabulation(n, height) << endl;
}
