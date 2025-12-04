#include <iostream>
#include <string>
using namespace std;

void computeLPS(string pattern, int lps[]) {
    int m = pattern.length();
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}


void kmp_search(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    int comparisons = 0;

    int lps[100];
    computeLPS(pattern, lps);

    int i = 0;
    int j = 0;

    while (i < n) {
        comparisons++;
        cout << "Comparing text[" << i << "]=" << text[i]
             << " with pattern[" << j << "]=" << pattern[j] << endl;

        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << (i - j) << endl;
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    cout << "\nTotal comparisons = " << comparisons << endl;
}

int main() {
    string text = "abcdeabcdeabcdef";
    string pattern = "abcdef";

    kmp_search(text, pattern);
    return 0;
}
