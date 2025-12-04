#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
};

class SuffixTrie {
private:
    TrieNode* root;

public:
    SuffixTrie() {
        root = new TrieNode();
    }

    void insertSuffix(const string& suffix) {
        TrieNode* node = root;
        for (char c : suffix) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
    }

    void buildSuffixTrie(const string& text) {
        for (int i = 0; i < text.length(); i++) {
            insertSuffix(text.substr(i));
        }
    }

    bool search(const string& pattern) {
        TrieNode* node = root;
        for (char c : pattern) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};

int main() {
    string text;
    cout << "Enter a string: ";
    cin >> text;

    text += "$"; // End symbol

    SuffixTrie trie;
    trie.buildSuffixTrie(text);

    cout << "\nSuffix Trie constructed for: " << text << endl;

    string pattern;
    cout << "\nEnter pattern to search: ";
    cin >> pattern;

    if (trie.search(pattern))
        cout << "Pattern found!" << endl;
    else
        cout << "Pattern not found!" << endl;

    return 0;
}
