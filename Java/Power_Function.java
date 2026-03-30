public class Power_Function {
    public static double Power(int x,int n){
        if(n==0){
            return 1;
        }
        if(n==1){
            return x;
        }
        if(x==0){
            return 0;
        }

        // Handle negative exponents: x^-n = 1 / x^n
        if (n < 0) {
            // We pass -n to make the exponent positive for the calculation,
            // then divide 1 by the result.
            return 1.0 / Power(x, -n);
        }

        double Half_Power=Power(x,n/2);

        if(n%2==0){
            // When Power is even
            return Half_Power*Half_Power;
        }
        else{
            // When Power is odd
            return x * Half_Power * Half_Power;
        }
    }
    public static void main(String[] args){
        int x=2;
        int n=5;

        System.out.println(Power(x,n));
    }
}
