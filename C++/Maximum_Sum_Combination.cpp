// Maximum Sum Combination

// You are given two integer arrays a[] and b[] of equal size. A sum combination is formed by adding one element from a[] and one from b[], using each index pair (i, j) at most once. Return the top k maximum sum combinations, sorted in non-increasing order.

// Examples:

// Input: a[] = [3, 2], b[] = [1, 4], k = 2
// Output: [7, 6]
// Explanation: Possible sums: 3 + 1 = 4, 3 + 4 = 7, 2 + 1 = 3, 2 + 4 = 6, Top 2 sums are 7 and 6.
// Input: a[] = [1, 4, 2, 3], b[] = [2, 5, 1, 6], k = 3
// Output: [10, 9, 9]
// Explanation: The top 3 maximum possible sums are : 4 + 6 = 10, 3 + 6 = 9, and 4 + 5 = 9

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>

using namespace std;

vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
    // code here
    sort(a.begin(),a.end(),greater<int>());
    sort(b.begin(),b.end(),greater<int>());
    
    vector<int> ans;
    
    priority_queue<pair<int,pair<int,int>>> pq;
    set<pair<int,int>> s;
    
    pq.push({a[0]+b[0],{0,0}});
    s.insert({0,0});
    
    for(int x=0;x<k;x++){
        int sum = pq.top().first;
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        
        ans.push_back(sum);
        pq.pop();
        
        if(i+1 < a.size() && s.find({i+1,j}) == s.end()){
            pq.push({a[i+1] + b[j],{i+1,j}});
            s.insert({i+1,j});
        }
        if(j+1 < b.size() && s.find({i,j+1}) == s.end()){
            pq.push({a[i] + b[j+1],{i,j+1}});
            s.insert({i,j+1});
        }
    }
    
    
    return ans;
}

int main() {
    int n,k;
    cin>>n>>k;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    
    vector<int> ans = topKSumPairs(a,b,k);
    for(int i=0;i<k;i++){
        cout<<ans[i]<<" ";
    }
    
    return 0;
}