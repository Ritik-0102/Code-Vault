// Euler Totient Function

// It is a function used to count the number of coprimes between 1 to n

// Coprime Numbers : Two numbers are said to be coprime if their GCD is 1


#include <iostream>

using namespace std;

// Approach 1 : Iterative GCD Method - O(n * log n) Time and O(1) Space
int gcd(int a, int b){
    if(a == 0){
        return b;
    }
    return gcd(b % a, a);
}

int eulerTotient(int n){
    int count = 0;
    for(int i = 1; i <= n; i++){
        if(gcd(i, n) == 1){
            count++;
        }
    }
    return count;
}

// Approach 2 : Euler’s Product Formula - O(sqrt(n)) Time and O(1) Space
int eulerTotient2(int n){
    int result = n; // Initialize result as n

    // Consider all prime factors of n and subtract their multiples from result
    for(int p = 2; p * p <= n; p++){
        // Check if p is a prime factor of n
        if(n % p == 0){
            // If yes, then update n and result
            while(n % p == 0){
                n /= p;
            }
            result -= result / p;
        }
    }

    // If n has a prime factor greater than sqrt(n)
    if(n > 1){
        result -= result / n;
    }

    return result;
}

int main() {
    int n = 11;

    return 0;
}