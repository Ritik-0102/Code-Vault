// https://www.geeksforgeeks.org/dsa/coprime-counting/

#include <iostream>
#include <vector>
using namespace std;

int coprimePairs(int n) {
    // Step 1: Initialization
    // Create an array to store the totient values. 
    // phi[i] will store the count of numbers less than i that are coprime to i.
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++) {
        phi[i] = i; 
    }

    // Step 2: Sieve Algorithm to compute Totient values
    for (int i = 2; i <= n; i++) {
        // If phi[i] hasn't changed from i, it means i is a prime number.
        if (phi[i] == i) {          
            // Iterate through all multiples of the prime number i.
            for (int j = i; j <= n; j += i) {
                // Apply Euler's product formula: phi(N) = N * (1 - 1/p)
                // This is algebraically equivalent to: phi[j] = phi[j] - (phi[j] / i)
                phi[j] -= phi[j] / i;
            }
        }
    }

    // Step 3: Accumulate Results
    int result = 0;

    // For each B from 2 to n, phi[B] gives the exact number of valid A values 
    // where 1 <= A <= B and gcd(A, B) = 1.
    for (int i = 2; i <= n; i++) {
        result += phi[i];
    }

    // Step 4: Handle Special Base Cases
    // The problem requires 0 <= A <= B. 
    // The only scenario where a number pairs with 0 and yields a GCD of 1 is gcd(0, 1) = 1.
    // For B = 1, there are two valid pairs: (0, 1) and (1, 1).
    if (n >= 1) {
        result += 2;
    }

    return result;
}

int main() {
    int n = 6;
    // Expected output for n = 6 is 13.
    cout << coprimePairs(n); 
    return 0;
}