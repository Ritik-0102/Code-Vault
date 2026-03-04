#include<iostream>
#include<vector>

using namespace std;

string Arrangement_is_neat_Or_Not(vector<int>& arr,int n){
    int count = 1;
    int extra = 0;
    
    for(int i=0;i<n;i++){
        if(arr[i] >= count){
            extra += arr[i] - count;
            count++;
        }
        else{
            if(extra + arr[i] >= count){
                extra = extra + arr[i] - count;
                count++;
            }
            else{
                return "NO";
            }
        }
    }

    return "YES";
}

using namespace std;

int main(){
    int no_of_test_cases;
    int n;

    cin >> no_of_test_cases;

    for(int i=0;i<no_of_test_cases;i++){
        cin >> n;
        vector<int> v(n);

        for(int i=0;i<n;i++){
            cin >> v[i];
        }

        cout << Arrangement_is_neat_Or_Not(v,n) << endl;
    }
}