// Pattern Print

//     1
//    2 2
//   3 3 3
//  4 4 4 4 
// 5 5 5 5 5

import java.util.Scanner;

public class Pattern_09 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);

        int n=sc.nextInt();

        for(int i=1;i<=n;i++){
            for(int j=0;j<n-i;j++){
                System.out.print(" ");
            }

            for(int j=0;j<i;j++){
                System.out.print(i + " ");
            }

            System.out.println();
        }

        sc.close();
    }
}
