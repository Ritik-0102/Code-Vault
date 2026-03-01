// Find the Inorder predecessor & Inorder successor in a BST for a given key

#include<iostream>
#include<vector>

using namespace std;

class TreeNode {
    public:
        int data;
        TreeNode *left;
        TreeNode *right;
        
        TreeNode(int data) {
            this->data = data;
            left = NULL;
            right = NULL;
        }
};

TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return new TreeNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// Find Predecessor :- Rightmost Node in the Left Subtree
TreeNode* RightmostNode(TreeNode* root){
    if(root == nullptr){
        return nullptr;
    }

    TreeNode* curr = root;

    while(curr->right != nullptr){
        curr = curr->right;
    }

    return curr;
}

// Find Successor :- Leftmost Node in the Right Subtree
TreeNode* LeftmostNode(TreeNode* root){
    if(root == nullptr){
        return nullptr;
    }

    TreeNode* curr = root;

    while(curr->left != nullptr){
        curr = curr->left;
    }

    return curr;
}

vector<TreeNode*> FindInorderPredec_And_Succe(TreeNode* root,int key){
    TreeNode* predecessor = nullptr;
    TreeNode* successor = nullptr;

    TreeNode* curr = root;

    while(curr != nullptr){
        if(key < curr->data){
            // If the key is less than the current node's data, move to the left subtree

            // we will mark curr as the possible successor
            successor = curr;
            curr = curr->left;
        }
        else if(key > curr->data){
            // If the key is greater than the current node's data, move to the right subtree

            // we will mark curr as the possible predecessor
            predecessor = curr;
            curr = curr->right;
        }
        else{
            // If the key is equal to the current node's data, we have found the node
            
            // Now we need to find the predecessor and successor of the node

            if(curr->left != nullptr){
                predecessor = RightmostNode(curr->left);
            }
            if(curr->right != nullptr){
                successor = LeftmostNode(curr->right);
            }

            break;
        }
    }

    return {predecessor, successor};
}

int main() {
    // Constructing a VALID Binary Search Tree
    //         50
    //       /    \
    //     30      70
    //    /  \    /  \
    //  20   40  60   80
    TreeNode* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    int key = 45;
    vector<TreeNode*> result = FindInorderPredec_And_Succe(root, key);

    cout << "Inorder Predecessor: " << result[0]->data << endl;
    cout << "Inorder Successor: " << result[1]->data << endl;

    return 0;
}