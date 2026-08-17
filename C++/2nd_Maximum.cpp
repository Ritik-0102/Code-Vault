#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int main(){
    vector<int> arr = {10,25,45,35,26};

    int maximum1 = INT_MIN;
    int maximum2 = INT_MIN;

    for(int i:arr){
        if(i > maximum1){
            maximum2 = maximum1;
            maximum1 = i;
        }
        else if(i > maximum2){
            maximum2 = i;
        }
    }

    cout << maximum1 << endl;
    cout << maximum2 << endl;
}