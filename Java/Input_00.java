import java.util.Scanner;

public class Input_00 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        String s=sc.next();  // This will only take sigle word input
        System.out.println(s);

        // sc.nextLine() is used to input full sentence

        sc.close();
    }
}
