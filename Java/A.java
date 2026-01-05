//         1
//       1   1
//     1   2   1
//   1   3   3   1
//  1  4   6   4   1

import java.util.ArrayList;
import java.util.List;

public class A {
    public static List<List<Integer>> pascalTriangle(int numRows) {
        // Initialize an empty list to store the rows of the triangle
        List<List<Integer>> triangle = new ArrayList<>();

        // Base case: if 0 rows are requested, return empty list
        if (numRows == 0) return triangle;

        for (int i = 0; i < numRows; i++) {
            List<Integer> row = new ArrayList<>();
            
            for (int j = 0; j <= i; j++) {
                // The first and last elements of every row are always 1
                if (j == 0 || j == i) {
                    row.add(1);
                } else {
                    // Fetch the previous row
                    List<Integer> prevRow = triangle.get(i - 1);
                    // Add the two numbers directly above the current position
                    row.add(prevRow.get(j - 1) + prevRow.get(j));
                }
            }
            // Add the constructed row to the triangle
            triangle.add(row);
        }
        
        return triangle;
    }

    public static void main(String[] args){
        int n = 5;
        System.out.println(pascalTriangle(n));
    }
}
