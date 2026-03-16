// Given an integer array nums, find the subarray with the largest sum, and return its sum.

// This problem will be solved by KADANE's algorithm

// Example 1:

// Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
// Explanation: The subarray [4,-1,2,1] has the largest sum 6.
// Example 2:

// Input: nums = [1]
// Output: 1
// Explanation: The subarray [1] has the largest sum 1.
// Example 3:

// Input: nums = [5,4,-1,7,8]
// Output: 23
// Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.


#include<iostream>

using namespace std;

int max_subarray_sum(int n,int arr[]){
    int max=INT8_MIN;

    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=i;j<n;j++){
            sum+=arr[j];
        }
        if(sum>max){
            max=sum;
        }
        if(sum<0){
            sum=0;
        }
    }

    return max;
}

int main(){
    int n=10;

    int arr[]={1,-2,3,5,7,-3,10,13,-8,15};

    for(int i=0;i<n;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << max_subarray_sum(n,arr);
}