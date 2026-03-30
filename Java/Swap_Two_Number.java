public class Swap_Two_Number {
    public static void main(String[] args) {
        int a = 5;
        int b = 9;

        System.out.println("Before Swap: a = " + a + ", b = " + b);

        // --- Start of XOR Swap ---
        a = a ^ b; 
        b = a ^ b; 
        a = a ^ b; 
        // --- End of XOR Swap ---

        System.out.println("After Swap:  a = " + a + ", b = " + b);
    }
}
