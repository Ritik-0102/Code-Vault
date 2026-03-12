

#include<iostream>

using namespace std;

int Max_container_area(int n,int arr[]){
    int x=0;
    int y=n;
    int max=(y-x-1)*min(arr[x],arr[y]);

    while(x<y){
        if(arr[x]<arr[y]){
            int temp=(y-x-2)*min(arr[x+1],arr[y]);
            if(temp>max){
                x++;
                max=(y-x-2)*min(arr[x],arr[y]);
            }
            else{
                y--;
            }
        }
        else{
            int temp=(y-x-2)*min(arr[x],arr[y-1]);
            if(temp>max){
                x++;
                max=(y-x-2)*min(arr[x],arr[y]);
            }
            else{
                y--;
            }
        }
    }
    return max;
}

int main(){
    int n=9;

    int arr[]={1,8,6,2,5,4,8,3,7};
    // int arr[]={1,1};

    for(int i=0;i<n;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << Max_container_area(n,arr);
}