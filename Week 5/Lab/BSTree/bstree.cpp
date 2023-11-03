#include "bstree.h"
#include <iostream>
#include "DynStack.h"

using namespace std;

bstree::bstree() { root = nullptr; }

// This recursive function clears every node in a tree structure
// It is triggered with the top/root node
void bstree::dhelper(tnode *node) {
    if (node != nullptr) {
        // TODO: Implement this recursive function (3 more lines)
        dhelper(node->right);
        dhelper(node->left);
        delete node;
    }
}

// This is the destructor, we will talk about this soon - don't worry, it just calls a function
// above which you need to complete
bstree::~bstree() { dhelper(root); }

// TODO: Listen the TA and digest this algorithm/function
bool bstree::shelper(int val, tnode *node) {
    if (node == nullptr)
        return false;
    else if (node->val == val)
        return true;
    else if (node->val > val)
        return (shelper(val, node->left));
    else if (node->val < val)
        return (shelper(val, node->right));
    else
        return false;
}

bool bstree::search(int val) { return (shelper(val, root)); }

// Note the use of reference variable
bool bstree::ihelper(int val, tnode *&node) {
    if (!node) {
        tnode *new_node = new tnode;
        new_node->val = val;
        new_node->left = nullptr;
        new_node->right = nullptr;
        node = new_node;
        return true;
    }

    if (node->val == val) return false;

    if (node->val > val) {
        if (node->left) {
            return ihelper(val, node->left);
        }
        tnode *new_node = new tnode;
        new_node->val = val;
        new_node->left = nullptr;
        new_node->right = nullptr;
        node->left = new_node;
        return true;
    }
    else {
        if (node->right) {
            return ihelper(val, node->right);
        }
        tnode *new_node = new tnode;
        new_node->val = val;
        new_node->left = nullptr;
        new_node->right = nullptr;
        node->right = new_node;
        return true;
    }
}

void bstree::insert(int val) {
    if (ihelper(val, root)) {
        cout << val << " is inserted." << endl;
    }
    else {
        cout << val << " already exists." << endl;
    }
}

void bstree::phelper(tnode *node) {
    if (!node) return;

    phelper(node->left);
    cout << node->val << " ";
    phelper(node->right);
}

void bstree::printInOrderRecursive() {
    phelper(root);
    cout << endl;
}

// This is a non-recursive replacement of the print function above
// It leverages a stack (instead of the recursion stack happening behind
// the scenes) - try to understand and complete this.
void bstree::printInOrderIterative() {
    DynStack stack;
    tnode *node = root;
    while (!stack.isEmpty() || node) {
        if (node) {
            // TODO: Implement this part (2 lines)
            stack.push(node);
            node = node->left;
        }
        else {
            // TODO: Implement this part (3 lines)
            stack.pop(node);
            cout << node->val << " ";
            node = node->right;
        }
    }
    cout << endl;
}

int main() {
    bstree mytree;

    mytree.insert(100);
    mytree.insert(3);
    mytree.insert(3);
    mytree.insert(5);
    mytree.insert(6);
    mytree.insert(9);
    mytree.insert(5);
    mytree.insert(8);
    cout << endl;

    cout << "Querying 3" << endl;
    if (mytree.search(3)) {
        cout << "3 is in the tree " << endl;
    }
    else {
        cout << "Could not find 3 " << endl;
    }
    cout << "Querying 51" << endl;
    if (mytree.search(51)) {
        cout << "51 is in the tree " << endl;
    }
    else {
        cout << "Could not find 51 " << endl;
    }

    cout << endl << endl;
    cout << "Printing recursive in order " << endl;
    mytree.printInOrderRecursive();
    cout << "Printing iterative in order " << endl;
    mytree.printInOrderIterative();

    return 0;
}
