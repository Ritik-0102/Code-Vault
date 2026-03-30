import java.util.Scanner;

public class If_else {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);

        int n=sc.nextInt();

        if(n == 0){
            System.out.println("number is zero");
        }
        else if(n>0){
            System.out.println("Number is Positive");
        }
        else{
            System.out.println("Number is Negative");
        }

        sc.close();
    }
    
}
