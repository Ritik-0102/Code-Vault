import java.util.Scanner;

// Rows are fixed 
// Columns are Not fixed

public class Jagged_Array {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int[][] arr=new int[3][];

        for(int i=0;i<3;i++){
            
            int columns=sc.nextInt();
            arr[i]=new int[columns];

            for(int j=0;j<columns;j++){
                arr[i][j]=sc.nextInt();
            }
        }


        for(int i=0;i<3;i++){
            for(int j=0;j<arr[i].length;j++){
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }

        sc.close();
    }
}
