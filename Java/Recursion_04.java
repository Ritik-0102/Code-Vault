// Print all subsets of a set of first n natural numbers

// n = 3
// subsets = [3, 2, 1] , [3, 2] , [3, 1] , [3] , [2, 1] , [2] , [1] , []

// Time Complexity: O(2^n)
// Space Complexity: O(n)

import java.util.ArrayList;

public class Recursion_04 {
    public static void print_subset(int n,ArrayList<Integer> subset){
        if(n==0){
            System.out.println(subset);
            return;
        }

        // include the element
        subset.add(n);
        print_subset(n-1,subset);

        // exclude the element
        subset.remove(subset.size()-1);
        print_subset(n-1,subset);
    }

    public static void main(String[] args){
        ArrayList<Integer> arr=new ArrayList<>();

        print_subset(3,arr);
    }
}
