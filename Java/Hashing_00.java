// Majority Element in an Array
// Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/3 ⌋ times. 

// Arr = [ 1, 2, 1, 2, 1, 2, 1, 2, 3 ]
// Output: [1 , 2]

// We can use a hash map to count the frequency of each element in the array. Then  we can iterate through the hash map to find the element that appears more than n/3 times.

// Time Complexity: O(n)
// Space Complexity: O(n)  

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Hashing_00 {
    
    public static List<Integer> majorityElement(int[] arr) {
        int n = arr.length;

        List<Integer> ans = new ArrayList<>();
        HashMap<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < n; i++) {
            if (map.containsKey(arr[i])) {
                map.put(arr[i], map.get(arr[i]) + 1);
            } else {
                map.put(arr[i], 1);
            }
        }
        
        for(int key : map.keySet()){
            if(map.get(key) > n/3){
                ans.add(key);
            }
        }

        return ans;
    }

    public static void main(String[] args) {
        int[] arr = { 1, 2, 1, 2, 1, 2, 1, 2, 3 };

        System.out.println("Majority Element: " + majorityElement(arr));
    }

}