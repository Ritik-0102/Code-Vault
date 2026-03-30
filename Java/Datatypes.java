import java.util.Scanner;

public class Datatypes {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int n=sc.nextInt();
        float f=sc.nextFloat();
        boolean b=sc.nextBoolean();
        char ch = sc.next().charAt(4);

        System.out.println(n);
        System.out.println(f);
        System.out.println(b);
        System.out.println(ch);
        sc.close();
    }
}
