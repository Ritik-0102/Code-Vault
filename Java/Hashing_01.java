// Union of 2 arrays
// arr1 = {7, 3, 9}
// arr2 = {6, 3, 9, 2, 9, 4}

// union = 6 (7, 3, 9, 6, 2, 4)

// Time Complexity: O(n)
// Space Complexity: O(n)

import java.util.*;

public class Hashing_01 {
    public static List<Integer> union(List<Integer> arr1, List<Integer> arr2) {
        HashSet<Integer> set = new HashSet<>();
        set.addAll(arr1);
        set.addAll(arr2);

        List<Integer> ans = new ArrayList<>();
        for (int i : set) {
            ans.add(i);
        }
        return ans;
    }

    public static void main(String[] args) {
        
        List<Integer> arr1 = new ArrayList<>(Arrays.asList(7, 3, 9));
        List<Integer> arr2 = new ArrayList<>(Arrays.asList(6, 3, 9, 2, 9, 4));

        System.out.println("Union: " + union(arr1, arr2));
    }
}
