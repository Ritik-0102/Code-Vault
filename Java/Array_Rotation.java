// create a ArrayRotator class with a constructor that takes an array and the number of positions to rotate in the right.

// Sample test cases :

// Input 1 :
// 7
// 3 6 9 8 5 2 1
// 3

// Output 1 :
// 5 2 1 3 6 9 8

// Input 2 :
// 5
// 63 95 74 65 98
// 1

// Output 2 :
// 98 63 95 74 65

// The Reversal Algorithm (Right Rotation)
// To rotate an array of size N by M positions to the right:
// Reverse the whole array.
// Reverse the first M elements.
// Reverse the remaining N - M elements.

// Example:Array: 
// [1, 2, 3, 4, 5], Rotate Right by 2
// Reverse Whole: [5, 4, 3, 2, 1]
// Reverse first 2 (5, 4): [4, 5, 3, 2, 1]
// Reverse rest (3, 2, 1): [4, 5, 1, 2, 3] -> Done.

import java.util.Arrays;

public class Array_Rotation {
    // Helper method to reverse a specific portion of the array
    public void reverse(int[] array,int start, int end) {
        while (start < end) {
            int temp = array[start];
            array[start] = array[end];
            array[end] = temp;
            start++;
            end--;
        }
    }

    public void rotateArray(int[] array,int positions) {
        int n = array.length;
        if (n == 0) return;
        
        // Handle cases where M > N (optional safety)
        positions = positions % n;

        // Handle negative positions (optional: makes it work for left rotation if you pass a negative number)
        if (positions < 0) {
            positions += n;
        }

        // Step 1: Reverse the whole array (0 to N-1)
        reverse(array,0, n - 1);

        // Step 2: Reverse the first M elements (0 to M-1)
        reverse(array,0, positions - 1);

        // Step 3: Reverse the remaining elements (M to N-1)
        reverse(array,positions, n - 1);
    }
    
    public static void main(String[] args) {
        // Instantiate the class to use the non-static methods
        Array_Rotation rotator = new Array_Rotation();
        
        // Sample data
        int[] myArray = {1, 2, 3, 4, 5, 6, 7};
        int rotateBy = 3;
        
        System.out.println("Original Array: " + Arrays.toString(myArray));
        
        // Call the method
        rotator.rotateArray(myArray, rotateBy);
        
        // Output the result
        System.out.println("Rotated Array (Right by " + rotateBy + "): " + Arrays.toString(myArray));
    }
}
