// Subarray sum equal to K

// arr = {1, 2, 3}  K=3 return number of such subarrays

// ans = 2 (1, 2) (3)

public class Hashing_04 {
    public static void main(String[] args) {
        int[] arr = {1, 2, 3};
        int k = 3;
        System.out.println(subarraySum(arr, k));
    }
}
