#include <iostream>
#include <string>
using namespace std;

void kmp_brute(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    int comparisons=0;
    for (int i = 0; i <= n - m; i++) {
        int temp = i;
        int j;
        for (j = 0; j < m; j++) {
            comparisons++;
            cout << "Comparing text[" << temp << "]=" << text[temp]<< " with pattern[" << j << "]=" << pattern[j] << endl;
            if (text[temp] != pattern[j]) {
                break;
            }
            temp++;
        }
        if (j == m) {
            cout << "Pattern found at index " << i << endl;
        }
    }
    cout << "\nTotal comparisons = " << comparisons << endl;
}

int main() {
    string text = "abcdeabcdeabcdef";
    string pattern = "abcdef";
    kmp_brute(text, pattern);
    return 0;
}
