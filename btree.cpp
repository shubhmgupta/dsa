#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    int degree;                  
    vector<int> keys;            
    vector<BTreeNode*> child;    
    int keyCount;                
    bool isLeaf;                 

    BTreeNode(int deg, bool leaf) {
        degree = deg;
        isLeaf = leaf;
        keys.assign(2 * degree - 1, 0);
        child.assign(2 * degree, nullptr);
        keyCount = 0;
    }

    void traverse() {
        int i;
        for (i = 0; i < keyCount; i++) {
            if (!isLeaf && child[i])
                child[i]->traverse();
            cout << keys[i] << " ";
        }
        if (!isLeaf && child[i])
            child[i]->traverse();
    }

    BTreeNode* search(int key) {
        int i = 0;
        while (i < keyCount && key > keys[i]) i++;

        if (i < keyCount && keys[i] == key)
            return this;

        if (isLeaf)
            return nullptr;

        return child[i]->search(key);
    }

    void insertNonFull(int key) {
        int i = keyCount - 1;

        if (isLeaf) {
            while (i >= 0 && keys[i] > key) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
            keyCount++;
        } else {
            while (i >= 0 && keys[i] > key) i--;
            i++;

            if (child[i]->keyCount == 2 * degree - 1) {
                splitChild(i, child[i]);

                if (keys[i] < key) i++;
            }
            child[i]->insertNonFull(key);
        }
    }

    void splitChild(int index, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->degree, y->isLeaf);
        z->keyCount = degree - 1;

        for (int j = 0; j < degree - 1; j++)
            z->keys[j] = y->keys[j + degree];

        if (!y->isLeaf) {
            for (int j = 0; j < degree; j++)
                z->child[j] = y->child[j + degree];
        }

        y->keyCount = degree - 1;

        for (int j = keyCount; j >= index + 1; j--)
            child[j + 1] = child[j];

        child[index + 1] = z;

        for (int j = keyCount - 1; j >= index; j--)
            keys[j + 1] = keys[j];

        keys[index] = y->keys[degree - 1];

        keyCount++;
    }
};


class BTree {
public:
    BTreeNode* root;
    int degree;

    BTree(int deg) {
        root = nullptr;
        degree = deg;
    }

    void traverse() {
        if (root) root->traverse();
        cout << "\n";
    }

    BTreeNode* search(int key) {
        return (root == nullptr) ? nullptr : root->search(key);
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(degree, true);
            root->keys[0] = key;
            root->keyCount = 1;
        } else {
            if (root->keyCount == 2 * degree - 1) {
                BTreeNode* newRoot = new BTreeNode(degree, false);
                newRoot->child[0] = root;
                newRoot->splitChild(0, root);

                int i = 0;
                if (newRoot->keys[0] < key) i++;
                newRoot->child[i]->insertNonFull(key);

                root = newRoot;
            } else {
                root->insertNonFull(key);
            }
        }
    }
};


int main() {
    int degree = 3;
    BTree bt(degree);

    vector<int> values = {10, 20, 5, 6, 12, 30, 7, 17};

    for (int x : values) bt.insert(x);

    cout << "B-Tree traversal: ";
    bt.traverse();

    int findKey = 6;
    if (bt.search(findKey))
        cout << "Key " << findKey << " found.\n";
    else
        cout << "Key " << findKey << " NOT found.\n";

    return 0;
}
