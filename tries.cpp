#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class TrieNode {
public:
    bool isEnd;
    unordered_map<char, TrieNode*> children;

    TrieNode() : isEnd(false) {}
};

class Trie {
private:
    TrieNode* root;

    // Helper for deletion
    bool deleteHelper(TrieNode* node, const string& word, int index) {
        if (index == word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return node->children.empty();
        }

        char ch = word[index];
        if (!node->children.count(ch))
            return false;

        TrieNode* next = node->children[ch];
        bool shouldDelete = deleteHelper(next, word, index + 1);

        if (shouldDelete) {
            delete next;
            node->children.erase(ch);
        }

        return node->children.empty() && !node->isEnd;
    }

    // Helper to collect autocomplete words
    void collect(TrieNode* node, string prefix, vector<string>& result) {
        if (node->isEnd)
            result.push_back(prefix);

        for (auto& pair : node->children)
            collect(pair.second, prefix + pair.first, result);
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch))
                node->children[ch] = new TrieNode();
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    // Search for an exact word
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch))
                return false;
            node = node->children[ch];
        }
        return node->isEnd;
    }

    // Check if any word starts with given prefix
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (!node->children.count(ch))
                return false;
            node = node->children[ch];
        }
        return true;
    }

    // Delete a word
    bool deleteWord(const string& word) {
        return deleteHelper(root, word, 0);
    }

    // Autocomplete all words starting with prefix
    vector<string> autoComplete(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (!node->children.count(ch))
                return {};
            node = node->children[ch];
        }

        vector<string> result;
        collect(node, prefix, result);
        return result;
    }
};

int main() {
    Trie trie;

    vector<string> words = {"apple", "app", "apply", "apt", "bat", "batch", "bath", "banana", "band"};
    for (auto& w : words)
        trie.insert(w);

    cout << boolalpha;
    cout << "search('app'): " << trie.search("app") << "\n";
    cout << "startsWith('ap'): " << trie.startsWith("ap") << "\n";

    auto suggestions = trie.autoComplete("ap");
    cout << "autocomplete('ap'): ";
    for (auto& s : suggestions) cout << s << " ";
    cout << "\n";

    trie.deleteWord("app");
    cout << "search('app') after delete: " << trie.search("app") << "\n";
    cout << "autocomplete('ap') after delete: ";
    for (auto& s : trie.autoComplete("ap")) cout << s << " ";
    cout << "\n";

    return 0;
}
