// Intersection of 2 arrays
// arr1 = {7, 3, 9}
// arr2 = {6, 3, 9, 2, 9, 4}

// intersection = (3, 9)

import java.util.*;

public class Hashing_02 {
    public static List<Integer> intersection(List<Integer> arr1, List<Integer> arr2) {
        List<Integer> ans = new ArrayList<>();

        HashSet<Integer> set1 = new HashSet<>();
        set1.addAll(arr1);
        HashSet<Integer> set2 = new HashSet<>();
        set2.addAll(arr2);

        for (int i : set1) {
            if (set2.contains(i)) {
                ans.add(i);
            }
        }

        return ans;
    }

    public static void main(String[] args) {
        List<Integer> arr1 = new ArrayList<>(Arrays.asList(7, 3, 9));
        List<Integer> arr2 = new ArrayList<>(Arrays.asList(6, 3, 9, 2, 9, 4));

        System.out.println("Intersection: " + intersection(arr1, arr2));
    }
}
