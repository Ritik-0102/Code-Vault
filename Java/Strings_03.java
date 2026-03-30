// Problem Statement

// Sophia is working on a program to combine two strings into a new one by concatenating their characters while ensuring that no character is repeated in the final result. 

// Write a program to merge two strings into one by retaining only unique characters in the order they first appear String builder class.

// Input format :
// The first line of input contains a string representing the firstString﻿.

// The second line contains a string representing the secondString.

// Output format :
// The output prints a string containing all unique characters from firstString and secondString in the order of their first appearance.

// Refer to the sample output for format specifications.

// Code constraints :
// In the given scenario, the test cases fall under the following constraints:

// 1 ≤ Length of each string ≤ 250 characters

// The input strings are case-sensitive.

// The input strings contain alphanumeric characters, special characters and spaces.

// Sample test cases :

// Input 1 :
// heLlo@123
// world@456
// Output 1 :
// heLlo@123wrd456

// Input 2 :
// aabbccddeeffgghhiijj
// jjiihhggffeeddccbbaa
// Output 2 :
// abcdefghij

// Input 3 :
// HarryPotter
// ChildPlay
// Output 3 :
// HaryPoteChild

import java.util.Scanner;

public class Strings_03 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s1 = sc.next();
        String s2 = sc.next();
        int[] arr = new int[128];
        for (int i = 0; i < s1.length(); i++) {
            arr[s1.charAt(i)]++;
        }
        for (int i = 0; i < s2.length(); i++) {
            arr[s2.charAt(i)]++;
        }
        for (int i = 0; i < s1.length(); i++) {
            if (arr[s1.charAt(i)] > 0) {
                System.out.print(s1.charAt(i));
                arr[s1.charAt(i)] = 0;
            }
        }
        for (int i = 0; i < s2.length(); i++) {
            if (arr[s2.charAt(i)] > 0) {
                System.out.print(s2.charAt(i));
                arr[s2.charAt(i)] = 0;
            }
        }
        sc.close();
    }

}
