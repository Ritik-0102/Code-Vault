// Recover BST

// You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

// We can swap the values of the nodes in the following way:
// 1. first we will find the anamoly pair of nodes (i.e. the nodes which are not in sorted order)
// 2. we store the value of fist node of first pair in a temp variable
// 3. we store the second node of last pair in a temp variable
// 4. we swap the values of first node of first pair and second node of last pair

// Time Complexity: O(n) - We traverse the tree once to find the anamoly pair and then swap the values of the nodes in the pair.
// Space Complexity: O(1) - We only use a constant amount of space to store the temporary variables.

#include<iostream>

using namespace std;

class TreeNode{
    public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data){
        val=data;
        left=NULL;
        right=NULL;
    }
};

void Recover_BST(TreeNode* Root,TreeNode* &prev,TreeNode* &first,TreeNode* &second){
    if(Root==NULL){
        return;
    }

    Recover_BST(Root->left,prev,first,second);

    if(prev!=NULL && Root->val < prev->val){
        if(first==NULL){
            first=prev;
        }
        second = Root;
    }
    prev = Root;

    Recover_BST(Root->right,prev,first,second);
}

void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    // Creating a tree: [3, 1, 4, null, null, 2]
    // Valid BST should be: 1, 2, 3, 4 (Inorder)
    // Swapped tree Inorder: 3, 2, 1, 4 (Here 1 and 3 are swapped)
    
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(2);

    cout << "Before Recovery: ";
    printInorder(root); // Output might look unsorted
    cout << endl;

    TreeNode* prev=NULL;
    TreeNode* first=NULL;
    TreeNode* second=NULL;

    Recover_BST(root,prev,first,second);

    // Swap The Values
    int temp=first->val;
    first->val=second->val;
    second->val=temp;

    cout << "After Recovery:  ";
    printInorder(root); // Should be sorted: 1 2 3 4
    cout << endl;

    return 0;
}