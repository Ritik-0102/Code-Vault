// leetcode 300
// https://leetcode.com/problems/longest-increasing-subsequence/

#include<iostream>
#include<vector>

using namespace std;


// Approach 1: Patience Sorting - O(nlogn)

class Solution {
public:
    // Binary Search to find the index of the first element in LIS that is >= x
    int helper(vector<int>& LIS,int x){
        int left = 0;
        int right = LIS.size()-1;

        while(left < right){
            int mid = left + (right - left)/2;

            // If mid element is greater than or equal to x, 
            // the answer is either at mid or to the left of mid.
            if(LIS[mid] >= x){
                right = mid;
            }
            // If mid element is strictly less than x,
            // the answer must be strictly to the right of mid.
            else{
                left = mid + 1;
            }
        }

        return left;
    }

    int lengthOfLIS(vector<int>& nums) {
        vector<int> LIS;

        for(int i:nums){
            // Case 1: LIS is empty OR current number is strictly greater than 
            // the last element in LIS. This means we can extend our longest sequence.
            if(LIS.empty() || LIS.back() < i){
                LIS.push_back(i);
            }
            // Case 2: Current number is smaller than or equal to the last element.
            // We use binary search to find the correct spot to overwrite.
            else{
                int idx = helper(LIS,i);

                // By replacing a larger number with a smaller one (i), 
                // we don't increase the length, but we create a "better" 
                // foundation for future numbers to attach to.
                LIS[idx] = i;
            }
        }

        // The size of the LIS array represents the length of the 
        // longest increasing subsequence found.
        return LIS.size();
    }
};


// Approach 2 : Dynamic Programming - Top-Down with Memoization - O(n*n)

class Solution {
public:
    int helper(vector<int>& nums,int idx,int prev,vector<vector<int>>& dp){
        if(idx >= nums.size()){
            return 0;
        }

        // Because the previous is initialized as -1 ,so we are accessing dp[idx][prev + 1]
        if(dp[idx][prev + 1] != -1){
            return dp[idx][prev + 1];
        }

        int pick = 0;
        if(prev == -1 || nums[prev] < nums[idx]){
            pick = 1 + helper(nums,idx+1,idx,dp);
        }

        int not_pick = helper(nums,idx+1,prev,dp);

        return dp[idx][prev + 1] = max(pick,not_pick);
    }

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> dp(n,vector<int>(n+1,-1));

        return helper(nums,0,-1,dp);
    }
};


//Approach 3 : Dynamic Programming - Top-Down with Memoization - O(n*n)

class Solution {
public:
    int n;
    int t[2501][2501];
    int lis(vector<int>& nums, int prev_idx, int curr_idx) {
       if(curr_idx == n)
           return 0;
        
        if(prev_idx != -1 && t[prev_idx][curr_idx] != -1)
            return t[prev_idx][curr_idx];
        
        int taken = 0;
        if(prev_idx == -1 || nums[curr_idx] > nums[prev_idx])
            taken = 1 + lis(nums, curr_idx, curr_idx+1);
        
        int not_taken = lis(nums, prev_idx, curr_idx+1);
        
        if(prev_idx != -1)
            t[prev_idx][curr_idx] =  max(taken, not_taken);
        
        return max(taken, not_taken);
            
    }
    int lengthOfLIS(vector<int>& nums) {
        memset(t, -1, sizeof(t));
        n = nums.size();
        return lis(nums, -1, 0);
    }
};

//Approach 4 : Dynamic Programming - Bottom-Up - O(n*n)

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> t(n, 1);
        int maxL = 1;
        for(int i = 0; i<n; i++) {
            for(int j = 0; j<i; j++) {
                if(nums[j] < nums[i]) {
                    t[i] = max(t[i], t[j]+1);
                    maxL = max(maxL, t[i]);
                }
            }
        }
        
        return maxL;
    }
};