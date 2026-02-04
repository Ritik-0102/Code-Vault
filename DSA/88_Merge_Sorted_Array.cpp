#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;       // Pointer for the last valid element in nums1
        int j = n - 1;       // Pointer for the last element in nums2
        int k = m + n - 1;   // Pointer for the last empty slot in nums1
        
        // While there are still elements in nums2 to merge
        while (j >= 0) {
            // If nums1 still has elements and the current nums1 element is larger
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } 
            // Otherwise, nums2's element is larger (or nums1 is empty)
            else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }
    }

int main()
{
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {2, 5, 6};
    int n = nums2.size();

    merge(nums1, m, nums2, n);

    for (int i = 0; i < nums1.size(); i++)
    {
        cout << nums1[i] << " ";
    }

    return 0;
}
