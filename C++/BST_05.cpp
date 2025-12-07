// Minimum Distance between BST Nodes

// It means we need to minimum difference between the values of any two nodes

// we will use a prev pointer to track the previous node
// and while Inorder traversal we will check the difference between current node and previous node
// and update the minimum difference

#include<iostream>
#include<climits>

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

TreeNode* previous=NULL;

int min_Diff_in_BST_nodes(TreeNode* Root){
    if(Root==NULL){
        return INT_MAX;
    }

    int ans=INT_MAX;

    if(Root->left!=NULL){
        int left_min=min_Diff_in_BST_nodes(Root->left);
        ans=min(ans,left_min);
    }

    if(previous!=NULL){
        ans=min(ans,Root->val - previous->val);
    }

    previous = Root;

    if(Root->right!=NULL){
        int Right_min=min_Diff_in_BST_nodes(Root->right);
        ans=min(ans,Right_min);
    }

    return ans;
}

int main() {
    // Example usage:
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    cout << "Minimum Difference: " << min_Diff_in_BST_nodes(root) << endl;

    return 0;
}