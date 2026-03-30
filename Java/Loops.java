import java.util.Scanner;

public class Loops {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int n=sc.nextInt();

        // For Loop
        for(int i=0;i<n;i++){
            System.out.println(i);
        }

        // While Loop
        int i = 0;
        while(i<n) {
        System.out.println(i);
        i++;
        }

        // Do While Loop
        int j = 0;
        do {
        System.out.println(j);
        j++;
        } while(j<n);



        sc.close();
    }
    
}
