// KMP - Knuth-Morris-Pratt Algorithm

// text = "ABABDABACDABABCABAB"
// pattern = "ABABCABAB"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Find the LPS (Longest Prefix Suffix) array for the pattern
void FindLPSArray(string pattern, vector<int> &lps){
    int n = pattern.size();

    // Initialize LPS array with zeros
    lps.assign(n, 0);

    int len = 0; // Length of the previous longest prefix suffix
    int i = 1; // Start from the second character

    while(i < n){
        if(pattern[i] == pattern[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len != 0){
                len = lps[len - 1]; // Use the previous LPS value
            }
            else{
                lps[i] = 0; // No prefix suffix found
                i++;
            }
        }
    }
}

void KMP(string text, string pattern){
	vector<int> lps;
	FindLPSArray(pattern, lps);

	int n = text.size();
	int m = pattern.size();
	int i = 0;
	int j = 0;

	while(i < n){
		if(pattern[j] == text[i]){
			j++;
			i++;
		}
		else{
			if(j != 0){
				j = lps[j - 1];
			}
			else{
				i++;
			}
		}
        if(j == m){
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
	}

}

int main(){
  string text = "ABABDABACDABABCABAB";
  string pattern = "ABAB";
  KMP(text, pattern);
  return 0;
}