

void sort(int arr[],int n){
    for(int i=0;i<n;i++){
        int min_idx=i;

        for(int j=i+1;j<n;j++){
            if(arr[min_idx]>arr[j]){
                min_idx=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[min_idx];
        arr[min_idx]=temp;
    }
}

int no_of_coins(int n,int arr[],int target){
    int coins=0;
    int sum=0;

    while(target>=sum){
        int freq=target/arr[i];
        ta
    }
}