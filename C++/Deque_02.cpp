// You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window which basically contains the max element in each window.

// LeetCode 239 -> Maximum Sliding Window Problem

#include<iostream>
#include<vector>
#include<deque>

using namespace std;

vector<int> max_sliding_window(vector<int> &arr,int k){
    vector<int> res; // to store the max of every windows
    deque<int> dq; // to store curr window elements

    // solve for 1st Window
    for(int i=0;i<k;i++){
        while(!dq.empty()  && arr[dq.back()]<arr[i]){
            dq.pop_back();
        }
        dq.push_back(i);
    }
    res.push_back(arr[dq.front()]);
    
    // solve for rest of the windows
    for(int i=k;i<arr.size();i++){
        // Remove the elements which does not belongs to the curr window
        if(!dq.empty()  && dq.front()==i-k){
            dq.pop_front();
        }

        // Remove all the elements less than the curr element from the deque
        while(!dq.empty()  && arr[dq.back()]<arr[i]){
            dq.pop_back();
        }

        dq.push_back(i);
        res.push_back(arr[dq.front()]);
    }

    return res;
}

int main(){
    vector<int> v={1,2,3,4,5,7,8,9};
    int k=3;

    vector<int> result = max_sliding_window(v,k);

    for(int n:result){
        cout << n << " ";
    }

    return 0;
}