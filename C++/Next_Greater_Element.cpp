#include<iostream>
#include<vector>
#include<stack>

using namespace std;

vector<int> Next_Greater_Element(vector<int>& arr,int n){
    vector<int> ans(n);
    stack<int> s;

    for(int i=n-1;i>=0;i--){
        while(!s.empty() && arr[i] >= s.top()){
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
    vector<int> arr = {6,8,0,1,3};

    int n = arr.size();

    vector<int> ans = Next_Greater_Element(arr,n);

    for(int i:ans){
        cout << i << " ";
    }
    // output : 8 -1 1 3 -1
}