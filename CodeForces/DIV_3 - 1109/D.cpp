#include<iostream>
#include<vector>

using namespace std;

int max_total_productivity(vector<int>& arr,vector<int>& posts,int n,int m){
    int max_productivity = 0;
    
    for(int i=0;i<n;i++){
        max_productivity += arr[i];
    }
    
    int productivity = max_productivity;

    for(int i=0;i<m;i++){
        for(int j=0;j<posts[i];j++){
            if(arr[j] < 0){
                productivity += (arr[j] + arr[j]);
                arr[j] = - arr[j];
            }
            else{
                productivity -= (arr[j] + arr[j]);
                arr[j] = - arr[j];
            }
        }
        max_productivity = max(max_productivity,productivity);
    }

    return max_productivity;
}

int main(){
    int no_of_test_cases;
    int n;
    int m;

    cin >> no_of_test_cases;

    for(int i=0;i<no_of_test_cases;i++){
        cin >> n >> m;
        vector<int> arr(n);
        vector<int> posts(m);

        for(int i=0;i<n;i++){
            cin >> arr[i];
        }

        for(int i=0;i<m;i++){
            cin >> posts[i];
        }

        cout << max_total_productivity(arr,posts,n,m) << endl;
    }
}