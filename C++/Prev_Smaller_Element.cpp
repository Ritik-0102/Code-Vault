#include<iostream>
#include<vector>
#include<stack>

using namespace std;

vector<int> Prev_Smaller_Element(vector<int>& arr,int n){
    vector<int> ans(n);
    stack<int> s;

    for(int i=0;i<n;i++){
        while(!s.empty() && arr[i] <= s.top()){
            s.pop();
        }

        if(s.empty()){
            ans[i] = -1;
        }
        else{
            ans[i] = s.top();
        }
        s.push(arr[i]);
    }

    return ans;
}

int main(){
    vector<int> arr = {3,1,0,8,6};

    int n = arr.size();

    vector<int> ans = Prev_Smaller_Element(arr,n);

    for(int i:ans){
        cout << i << " ";
    }
    // output : -1 -1 -1 0 0
}