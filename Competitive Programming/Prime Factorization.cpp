#include<iostream>

using namespace std;

void primeFactors(long long n) {
    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }

    if (n > 1)
        cout << n;
}

int main() {
    long long n = 84;
    primeFactors(n);
    return 0;
}