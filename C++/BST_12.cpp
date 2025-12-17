// Largest BST in Binary Tree

// We need to find the BST in Binary Tree which has the largest size (no. of nodes)

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

class Info{
    public:
    int min;
    int max;
    int size;

    Info(int min,int max,int size){
        this->min=min;
        this->max=max;
        this->size=size;
    }
};

Info* Largest_BST(TreeNode* Root){
    // Base Case: An empty tree is a valid BST of size 0.
    // We return max possible min, and min possible max so leaf nodes pass the check.
    if(Root==NULL){
        return new Info(INT_MAX,INT_MIN,0);
    }
    
    // 1. Post-order traversal (Left, Right, Node)
    Info* left=Largest_BST(Root->left);
    Info* right=Largest_BST(Root->right);
    
    // 2. Check if current subtree forms a valid BST
    if(Root->val > left->max && Root->val < right->min){
        int currMin = min(Root->val,left->min);
        int currMax = max(Root->val,right->max);
        int currSize = left->size + right->size + 1;

        return new Info(currMin,currMax,currSize);
    }
    else{
        // 3. If it's NOT a valid BST, pass up the largest size found so far.
        // We set min to INT_MIN and max to INT_MAX so ancestors will definitely fail the BST check.
        return new Info(INT_MIN,INT_MAX,max(left->size,right->size));
    }
}
int main(){
    TreeNode* Root = NULL;

    //    4
    //   / \
    //  2   5
    // / \ / \
    // 1 3 6 7

    Root = new TreeNode(4);
    Root->left = new TreeNode(2);
    Root->right = new TreeNode(6);
    Root->left->left = new TreeNode(1);
    Root->left->right = new TreeNode(3);
    Root->right->left = new TreeNode(5);
    Root->right->right = new TreeNode(7);

    Info* ans = Largest_BST(Root);
    cout<<"Largest BST Size : "<< ans->size << endl;

    return 0;
}