// Subarray sum equal to K

// arr = {1, 2, 3}  K=3 return number of such subarrays

// ans = 2 (1, 2) (3)

public static int subarraySum(int[] arr, int k) {
    int count = 0;
    for (int i = 0; i < arr.length; i++) {
        int sum = 0;
        for (int j = i; j < arr.length; j++) {
            sum += arr[j];
            if (sum == k) {
                count++;
            }
        }
    }
    return count;
}

public class Hashing_04 {
    public static void main(String[] args) {
        int[] arr = {1, 2, 3};
        int k = 3;
        System.out.println(subarraySum(arr, k));
    }
}
