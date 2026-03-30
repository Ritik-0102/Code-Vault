// Time Complexity :- O(n^2)

public class Selection_Sort {
    public static void main(String[] args){
        int[] arr= {1 , 4 , 7 , 5 , 8 , 9 , 0 , -1};

        for(int i=0;i<8;i++){
            int smallest=i;
            for(int j=i+1;j<8;j++){
                if(arr[j]<arr[smallest]){
                    smallest=j;
                }
            }

            int temp=arr[i];
            arr[i]=arr[smallest];
            arr[smallest]=temp;
        }


        for(int i:arr){
            System.out.print(i + " ");
        }
    }
}
