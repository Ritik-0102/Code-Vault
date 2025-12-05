// Deleting A Node From BST

#include<iostream>
#include<vector>

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

TreeNode* InsertNode(TreeNode* Root,int val){
    if(Root==NULL){
        return new TreeNode(val);
    }
    if(val<Root->val){
        Root->left = InsertNode(Root->left,val);
    }
    else{
        Root->right = InsertNode(Root->right,val);
    }

    return Root;
}

TreeNode* Build_BST(vector<int> &v){
    TreeNode* Root=NULL;

    for(int i:v){
        Root=InsertNode(Root,i);
    }

    return Root;
}

// Helper function to find the Inorder Successor (Smallest in Right Subtree)
TreeNode* FindIS(TreeNode* root){
        while(root->left != nullptr){
            root = root->left;
        }

        return root;
    }

    TreeNode* deleteNode(TreeNode* root, int key){
        if(root == nullptr){
            return nullptr;
        }

        if(root->val > key){
            root->left = deleteNode(root->left,key);
        }
        else if(root->val < key){
            root->right = deleteNode(root->right,key);
        }
        else{
            // root->val == key

            // Case 1 & 2 : when there is 0 OR 1 childs exist for node to be deleted
            if(root->left == nullptr){
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if(root->right == nullptr){
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            else{
                // Case 3 : when there is 2 childs exist for node to be deleted

                // 1. Find Inorder Successor
                TreeNode* IS = FindIS(root->right);

                // 2. Now copy value IS into root node 
                root->val = IS->val;

                // 3. now delete the IS
                root->right = deleteNode(root->right,IS->val);
            }
        }

        return root;
    }

void Inorder_Traversal(TreeNode* Root){
    if(Root==NULL){
        return ;
    }

    Inorder_Traversal(Root->left);
    cout << Root->val << "  ";
    Inorder_Traversal(Root->right);
}

int main(){
    int n;
    vector<int> v={3,2,1,5,6,4};

    TreeNode* Root = Build_BST(v);

    Inorder_Traversal(Root);
    cout << endl;
    
    Root=deleteNode(Root,3);
    
    Inorder_Traversal(Root);
    cout << endl;
}