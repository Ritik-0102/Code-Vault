public class Fibonacci{
    public static void Fibonacci_00(int a,int b,int n){
        if(n==0){
            return;
        }

        int c=a+b;
        System.out.print(c + " ");
        Fibonacci_00(b,c,n-1);
    }

    public static int Fibonacci_01(int n){
        if (n <= 1) return n;
        return Fibonacci_01(n-1) + Fibonacci_01(n-2);
    }


    public static int Fibonacci_02(int n){
        int arr[] = new int[n];

        arr[0]=0;
        arr[1]=1;

        for(int i=2;i<n;i++){
            arr[i]=arr[i-1]+arr[i-2];
        }

        return arr[n-1];
    }


    public static int Fibonacci_03(int n){
        int a=0;
        int b=1;
        int c=1;

        for(int i=2;i<n;i++){
            c=a+b;
            a=b;
            b=c;
        }

        return c;
    }


    public static void main(String[] args) {
        int n=7;

        System.out.print(0 + " ");
        System.out.print(1 + " ");

        Fibonacci_00(0,1,n-2);

        System.out.println();

        System.out.println(Fibonacci_01(4));
        System.out.println(Fibonacci_02(5));
        System.out.println(Fibonacci_03(5));

    }
}
