// Time Complexity :- O(n^2)

public class Insertion_Sort {
    public static void main(String[] args){
        int[] arr= {1 , 4 , 7 , 5 , 8 , 9 , 0 , -1};

        for(int i=1;i<8;i++){
            int current=arr[i];
            int j=i-1;
            while(j>=0 && current<arr[j]){
                arr[j+1]=arr[j];
                j--;
            }

            arr[j+1]=current;
        }


        for(int i:arr){
            System.out.print(i + " ");
        }
    }
}
