// Bottom View Of Binary Tree

/*
        1
       / \
      2   3
         / \
        4   5
*/

// Bottom View :- 2 , 4 , 3 , 5

#include<iostream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

class Tree_Node{
    public:
    int val;
    Tree_Node* left;
    Tree_Node* right;

    Tree_Node(int data){
        val = data;
        left = NULL;
        right = NULL;
    }
};

void Bottom_view(Tree_Node* Root){
    if(Root == NULL) return; // Always good practice to handle empty trees

    queue<pair<Tree_Node*, int>> q; // (Tree Node , HD)
    map<int, int> m; // (HD , value)

    q.push({Root, 0});

    while(q.size() > 0){
        Tree_Node* curr_node = q.front().first;
        int curr_HD = q.front().second;

        q.pop();

        // THE ONLY DIFFERENCE: Overwrite the map every single time!
        // The last node processed at this HD will be the lowest one in the tree.
        m[curr_HD] = curr_node->val;

        if(curr_node->left != NULL){
            q.push({curr_node->left, curr_HD - 1});
        }

        if(curr_node->right != NULL){
            q.push({curr_node->right, curr_HD + 1});
        }
    }

    for(auto ele : m){
        cout << ele.second << "  ";
    }
}

int main(){
    // Tree Node
    //      1
    //     / \
    //    2   3
    //       / \
    //      4   5

    Tree_Node* Root = new Tree_Node(1);
    Root->left = new Tree_Node(2);
    Root->right = new Tree_Node(3);
    Root->right->left = new Tree_Node(4);
    Root->right->right = new Tree_Node(5);

    Bottom_view(Root);

    return 0;
}