import java.util.Scanner;

public class Ternary_Operator {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int a=sc.nextInt();
        int b=sc.nextInt();
        int c=sc.nextInt();

        int res = a>b ? a>c ? a : c : b>c ? b : c;

        System.out.println(res);

        sc.close();
    }
}
