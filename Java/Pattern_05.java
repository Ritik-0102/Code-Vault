// Pattern print

// 1
// 2 3
// 4 5 6
// 7 8 9 10
// 11 12 13 14 15

import java.util.Scanner;

public class Pattern_05 {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int n=sc.nextInt();
        int x=1;

        for(int i=0;i<n;i++){
            for(int j=0;j<=i;j++){
                System.out.print((x++) + " ");
            }
            System.out.println();
        }

        sc.close();
    }
}
