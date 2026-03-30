// Problem Statement:

// Anu is tasked with creating a program to determine whether a given number or a range of numbers falls into one of two categories: prime numbers or Fibonacci numbers. There are two constructors to achieve this task:

// Single Number Checker
// Constructor: PrimeFibonacciChecker(int number, String type)

// Range Checker
// Constructor: PrimeFibonacciChecker(int start, int end, String type)
// Input format :
// The first line of input contains either a single integer x (for a single number check) or two integers start, and end separated by a space (for a range check).
// The second line contains a string type, which can be either "prime" or "fibonacci," indicating the type of check to perform.
// Output format :
// For single number check:
// If the type is "prime" and the number is prime, print: <number> is a prime number.
// If the type is "prime" and the number is not prime, print: <number> is not a prime number.
// If the type is "fibonacci" and the number belongs to the Fibonacci series, print: <number> is part of the Fibonacci series.
// If the type is "fibonacci" and the number does not belong to the Fibonacci series, print: <number> is not part of the Fibonacci series.

// For range check:
// If the type is "prime", print all prime numbers in the given range in list format: "Prime numbers in the range <start> to <end>: [list]"
// If the type is "fibonacci", print all Fibonacci numbers in the given range in list format: "Fibonacci numbers in the range <start> to <end>: [list]"

// For invalid type:
// If the given type is neither "prime" nor "fibonacci", print: "Invalid type specified."

// Refer to the sample output for formatting specifications.
// Code constraints :
// The given testcases fall under the following constraints:
// 1 ≤ x ≤ 100
// Sample test cases :
// Input 1 :
// 41
// prime
// Output 1 :
// 41 is a prime number.
// Input 2 :
// 17
// fibonacci
// Output 2 :
// 17 is not part of the Fibonacci series.
// Input 3 :
// 10 20
// prime
// Output 3 :
// Prime numbers in the range 10 to 20: [11, 13, 17, 19]
// Input 4 :
// 10
// invalid
// Output 4 :
// Invalid type specified.



// import java.util.ArrayList;
// import java.util.Scanner;

// class PrimeFibonacciChecker {
// private int number;
// private int start;
// private int end;
// private String type;
// private boolean isRange;

// // Constructor 1: Single Number Checker
// public PrimeFibonacciChecker(int number, String type) {
// this.number = number;
// this.type = type;
// this.isRange = false;
// process();
// }

// // Constructor 2: Range Checker
// public PrimeFibonacciChecker(int start, int end, String type) {
// this.start = start;
// this.end = end;
// this.type = type;
// this.isRange = true;
// process();
// }

// // Main processing logic
// private void process() {
// // Validation for invalid types
// if (!type.equals("prime") && !type.equals("fibonacci")) {
// System.out.println("Invalid type specified.");
// return;
// }

// if (isRange) {
// handleRangeCheck();
// } else {
// handleSingleCheck();
// }
// }

// // Logic for Single Number
// private void handleSingleCheck() {
// if (type.equals("prime")) {
// if (isPrime(number)) {
// System.out.println(number + " is a prime number.");
// } else {
// System.out.println(number + " is not a prime number.");
// }
// } else if (type.equals("fibonacci")) {
// if (isFibonacci(number)) {
// System.out.println(number + " is part of the Fibonacci series.");
// } else {
// System.out.println(number + " is not part of the Fibonacci series.");
// }
// }
// }

// // Logic for Range
// private void handleRangeCheck() {
// ArrayList<Integer> resultList = new ArrayList<>();

// if (type.equals("prime")) {
// for (int i = start; i <= end; i++) {
// if (isPrime(i)) {
// resultList.add(i);
// }
// }
// System.out.println("Prime numbers in the range " + start + " to " + end + ":
// " + resultList);
// } else if (type.equals("fibonacci")) {
// for (int i = start; i <= end; i++) {
// if (isFibonacci(i)) {
// resultList.add(i);
// }
// }
// System.out.println("Fibonacci numbers in the range " + start + " to " + end +
// ": " + resultList);
// }
// }

// // Utility: Check if Prime
// private boolean isPrime(int n) {
// if (n <= 1) return false;
// for (int i = 2; i * i <= n; i++) {
// if (n % i == 0) return false;
// }
// return true;
// }

// // Utility: Check if Fibonacci
// // A number is Fibonacci if 5*n*n + 4 or 5*n*n - 4 is a perfect square
// private boolean isFibonacci(int n) {
// if (n < 0) return false;
// return isPerfectSquare(5 * n * n + 4) || isPerfectSquare(5 * n * n - 4);
// }

// private boolean isPerfectSquare(int x) {
// int s = (int) Math.sqrt(x);
// return s * s == x;
// }
// }

// public class Prime_Fibonacci_Checker {
// public static void main(String[] args) {
// Scanner sc = new Scanner(System.in);

// // Read the entire first line to determine if it is one or two numbers
// if (sc.hasNextLine()) {
// String line1 = sc.nextLine().trim();
// String type = sc.nextLine().trim();

// String[] parts = line1.split("\\s+"); // Split by whitespace

// if (parts.length == 1) {
// // Single number case
// int number = Integer.parseInt(parts[0]);
// new PrimeFibonacciChecker(number, type);
// } else if (parts.length == 2) {
// // Range case
// int start = Integer.parseInt(parts[0]);
// int end = Integer.parseInt(parts[1]);
// new PrimeFibonacciChecker(start, end, type);
// }
// }
// sc.close();
// }
// }

import java.util.*;
import java.util.ArrayList;

class PrimeFibonacciChecker {

    boolean isPrime(int n) {
        if (n <= 1)
            return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    boolean isFibonacci(int n) {
        if (n == 0 || n == 1)
            return true;

        int a = 0;
        int b = 1;
        int c = a + b;

        while (c < n) {
            a = b;
            b = c;
            c = a + b;
        }

        if (c == n) {
            return true;
        } else {
            return false;
        }
    }

    PrimeFibonacciChecker(int a, String s) {
        if (s.equals("prime")) {
            if (isPrime(a)) {
                System.out.println(a + " is a prime number.");
            } else {
                System.out.println(a + " is not a prime number.");
            }
        } else if (s.equals("fibonacci")) {
            if (isFibonacci(a)) {
                System.out.println(a + " is part of the Fibonacci series.");
            } else {
                System.out.println(a + " is not part of the Fibonacci series.");
            }
        } else {
            System.out.println("Invalid type specified.");
        }
    }

    PrimeFibonacciChecker(int a, int b, String s) {
        if (s.equals("prime")) {
            ArrayList<Integer> li = new ArrayList<>();
            for (int i = a; i <= b; i++) {
                if (isPrime(i)) {
                    li.add(i);
                }
            }
            System.out.println("Prime numbers in the range " + a + " to " + b + ": " + li);
        } else if (s.equals("fibonacci")) {
            ArrayList<Integer> li = new ArrayList<>();
            for (int i = a; i <= b; i++) {
                if (isFibonacci(i)) {
                    li.add(i);
                }
            }
            System.out.println("Fibonacci numbers in the range " + a + " to " + b + ": " + li);
        } else {
            System.out.println("Invalid type specified.");
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        if (sc.hasNextLine()) {
            String firstLine = sc.nextLine().trim();
            String type = sc.nextLine().trim();

            String[] nums = firstLine.split(" ");

            if (nums.length == 1) {
                int num = Integer.parseInt(nums[0]);
                new PrimeFibonacciChecker(num, type);
            } else if (nums.length == 2) {
                int start = Integer.parseInt(nums[0]);
                int end = Integer.parseInt(nums[1]);
                new PrimeFibonacciChecker(start, end, type);
            }
        }
        sc.close();
    }
}


/* 
import java.util.*;
import java.util.ArrayList;

class Prime_Fibonacci_Checker{
    boolean isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

   boolean isFibonacci(int n) {
        int a=0;
        int b=1;
        int c=a+b;

        while(c<n){
            a=b;
            b=c;
            c=a+b;
        }

        if(c==n){
            return true;
        }
        else{
            return false;
        }
    }

    Prime_Fibonacci_Checker(int a,String s){
        if(s.compareTo("prime")==0){
            if(isPrime(a)){
                System.out.println(a + " is a prime number.");
            }
            else{
                System.out.println(a + " is not a prime number.");
            }
        }
        else if(s.compareTo("fibonacci")==0){
            if(isFibonacci(a)){
                System.out.println(a + " is part of the Fibonacci series.");
            }
            else{
                System.out.println(a + " is not part of the Fibonacci series.");
            }
        }
        else{
            System.out.println("Invalid type specified");
        }
    }
    
    
    Prime_Fibonacci_Checker(int a,int b,String s){
        if(s.compareTo("prime")==0){
            ArrayList<Integer> li = new ArrayList<>();
            for(int i=a;i<=b;i++){
                if(isPrime(i)){
                    li.add(i);
                }
            }

            System.out.println("Prime numbers in the range" + a +  " to " + b + " : " + li);
        }
        else if(s.compareTo("fibonacci")==0){
            ArrayList<Integer> li = new ArrayList<>();
            for(int i=a;i<=b;i++){
                if(isFibonacci(i)){
                    li.add(i);
                }
            }

            System.out.println("Fibonacci numbers in the range" + a +  " to " + b + " : " + li);
        }
        else{
            System.out.println("Invalid type specified");
        }
    }
}

*/