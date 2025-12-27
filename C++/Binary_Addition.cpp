#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// This is the first solution I came up with
// It works, but it's not optimal

string addBinary_1(string a, string b)
{
    string ans = "";

        int carry = 0;
        int i = a.size() - 1;
        int j = b.size() - 1;
        while(i >= 0 && j >= 0){
            if(a[i] == '0' && b[j] == '0'){
                if(carry == 1){
                    ans += '1';
                    carry = 0;
                }
                else{
                    ans += '0';
                }                
            }
            else if(a[i] == '1' && b[j] == '1'){
                if(carry == 1){
                    ans += '1';
                }
                else{
                    ans += '0';
                    carry = 1;
                }
            }
            else{
                if(carry == 1){
                    ans += '0';
                }
                else{
                    ans += '1';
                }
            }
            i--;
            j--;
        }

        while(i >= 0){
            if(a[i] == '1' && carry == 1){
                ans += '0';
            }
            else if(a[i] == '0' && carry == 1){
                ans += '1';
                carry = 0;
            }
            else{
                ans += a[i];
            }
            i--;
        }
        while(j >= 0){
            if(b[j] == '1' && carry == 1){
                ans += '0';
            }
            else if(b[j] == '0' && carry == 1){
                ans += '1';
                carry = 0;
            }
            else{
                ans += b[j];
            }
            j--;
        }

        if(carry == 1){
            ans += '1';
        }

        reverse(ans.begin(),ans.end());

        return ans;
}

// This is the second solution I came up with
// It is optimal

string addBinary_2(std::string a, std::string b)
{
    string ans = "";
    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0;

    // Loop runs as long as there is a character in 'a', 'b', OR a leftover carry
    while (i >= 0 || j >= 0 || carry > 0)
    {
        int sum = carry;

        // Subtracting '0' converts the char to an actual integer value (0 or 1)
        if (i >= 0)
        {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0)
        {
            sum += b[j] - '0';
            j--;
        }

        // If sum is 0 (0%2=0), 1 (1%2=1), 2 (2%2=0), 3 (3%2=1)
        ans += to_string(sum % 2);

        // If sum is 0 or 1, carry is 0. If sum is 2 or 3, carry is 1.
        carry = sum / 2;
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

int main()
{
    string a = "1010";
    string b = "1011";

    cout << addBinary_1(a, b) << endl;
    cout << addBinary_2(a, b) << endl;

    return 0;
}