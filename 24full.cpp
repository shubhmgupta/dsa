#include <iostream>
#include <vector>
using namespace std;

// A node of 2-3-4 tree (B-tree with minimum degree = 2)
class Node {
public:
    int degree;                 // minimum degree (for 2-4 tree degree = 2)
    vector<int> keys;           // keys (max 2*degree - 1 => 3 for 2-4 tree)
    vector<Node*> child;        // children pointers (max 2*degree => 4)
    int keyCount;               // current number of keys
    bool isLeaf;                // leaf flag

    Node(int deg, bool leaf) {
        degree = deg;
        isLeaf = leaf;
        keys.assign(2 * degree - 1, 0);
        child.assign(2 * degree, nullptr);
        keyCount = 0;
    }
};

// 2-3-4 Tree class
class TwoFourTree {
public:
    Node* root;
    int degree; // for 2-4 tree, degree = 2

    TwoFourTree(int deg = 2) {
        root = nullptr;
        degree = deg;
    }

    // In-order traversal
    void traverse() {
        if (root != nullptr) traverseUtil(root);
        cout << "\n";
    }

    void traverseUtil(Node* node) {
        if (!node) return;
        int i;
        for (i = 0; i < node->keyCount; i++) {
            // traverse child[i]
            if (!node->isLeaf && node->child[i] != nullptr)
                traverseUtil(node->child[i]);
            // print key
            cout << node->keys[i] << " ";
        }
        // traverse last child
        if (!node->isLeaf && node->child[i] != nullptr)
            traverseUtil(node->child[i]);
    }

    // Search a key in the tree
    Node* search(int key) {
        return (root == nullptr) ? nullptr : searchUtil(root, key);
    }

    Node* searchUtil(Node* node, int key) {
        int i = 0;
        // find the first key greater than or equal to key
        while (i < node->keyCount && key > node->keys[i]) i++;

        // if found equal, return node
        if (i < node->keyCount && node->keys[i] == key)
            return node;

        // if leaf and not found
        if (node->isLeaf)
            return nullptr;

        // go to the correct child
        return searchUtil(node->child[i], key);
    }

    // Split child y of node x at index idx
    // x is non-full when called
    void splitChild(Node* x, int idx) {
        Node* y = x->child[idx];
        // create new node z which will store (degree-1) keys of y
        Node* z = new Node(y->degree, y->isLeaf);
        z->keyCount = degree - 1; // for degree=2, degree-1 =1

        // copy last (degree-1) keys of y to z
        for (int j = 0; j < degree - 1; j++)
            z->keys[j] = y->keys[j + degree];

        // copy the child pointers if y is not leaf
        if (!y->isLeaf) {
            for (int j = 0; j < degree; j++)
                z->child[j] = y->child[j + degree];
        }

        // reduce the key count of y
        y->keyCount = degree - 1;

        // make space for new child in x
        for (int j = x->keyCount; j >= idx + 1; j--)
            x->child[j + 1] = x->child[j];

        // link new child to x
        x->child[idx + 1] = z;

        // move keys in x to make space for middle key of y
        for (int j = x->keyCount - 1; j >= idx; j--)
            x->keys[j + 1] = x->keys[j];

        // middle key of y goes up to x
        x->keys[idx] = y->keys[degree - 1];

        // increment key count of x
        x->keyCount = x->keyCount + 1;
    }

    // Insert a new key in the subtree rooted with node
    // node is assumed non-full when this is called
    void insertNonFull(Node* node, int key) {
        int i = node->keyCount - 1;

        if (node->isLeaf) {
            // find location of new key to be inserted and move all greater keys one space ahead
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }

            node->keys[i + 1] = key;
            node->keyCount = node->keyCount + 1;
        } else {
            // find the child which is going to have the new key
            while (i >= 0 && node->keys[i] > key) i--;
            i++; // now child index to go

            // if the child is full, split it
            if (node->child[i]->keyCount == 2 * degree - 1) {
                splitChild(node, i);

                // after split, the middle key of child moves up and node's child[i] and child[i+1] are two halves
                // decide which of the two will have the new key
                if (node->keys[i] < key)
                    i++;
            }
            insertNonFull(node->child[i], key);
        }
    }

    // Insert a key to the 2-4 tree
    void insert(int key) {
        // If tree is empty
        if (root == nullptr) {
            root = new Node(degree, true);
            root->keys[0] = key;
            root->keyCount = 1;
            return;
        }

        // If root is full, tree grows in height
        if (root->keyCount == 2 * degree - 1) {
            Node* s = new Node(degree, false);

            // old root becomes child of new root
            s->child[0] = root;

            // split the old root and move one key to new root
            splitChild(s, 0);

            // new root has two children now. Decide which child will have the new key
            int i = 0;
            if (s->keys[0] < key) i++;
            insertNonFull(s->child[i], key);

            // change root
            root = s;
        } else {
            insertNonFull(root, key);
        }
    }

    // Utility to print nodes level by level (for debugging)
    void printStructure() {
        if (!root) {
            cout << "Tree is empty\n";
            return;
        }
        cout << "Tree structure (node: keys):\n";
        printLevel(root, 0);
    }

    void printLevel(Node* node, int level) {
        if (!node) return;
        cout << "Level " << level << ": (";
        for (int i = 0; i < node->keyCount; i++) {
            cout << node->keys[i];
            if (i + 1 < node->keyCount) cout << ",";
        }
        cout << ")\n";
        if (!node->isLeaf) {
            for (int i = 0; i <= node->keyCount; i++) {
                printLevel(node->child[i], level + 1);
            }
        }
    }

    // Destructor helper to free memory
    void clear(Node* node) {
        if (!node) return;
        if (!node->isLeaf) {
            for (int i = 0; i <= node->keyCount; i++)
                clear(node->child[i]);
        }
        delete node;
    }

    ~TwoFourTree() {
        clear(root);
    }
};

// Example usage
int main() {
    TwoFourTree tree(2); // degree = 2 for 2-4 tree

    // Sample insertions
    vector<int> values = {10, 20, 5, 6, 12, 30, 7, 17, 3, 1, 2, 8, 9, 4, 15};
    for (int v : values) {
        tree.insert(v);
    }

    cout << "In-order traversal of 2-4 tree:\n";
    tree.traverse();

    cout << "\nStructure of tree:\n";
    tree.printStructure();

    // Search tests
    int toFind[] = {6, 15, 100};
    for (int k : toFind) {
        Node* res = tree.search(k);
        if (res) cout << "Key " << k << " found.\n";
        else cout << "Key " << k << " NOT found.\n";
    }

    return 0;
}
