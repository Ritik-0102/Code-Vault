// Zig - Zag Printing of Binary Tree

/*
            6
          /   \
         9     7
        /\     /\
       3  6   5  1   

*/

// Output :- 6 , 9 , 7 , 1 , 5 , 6 , 3
// Means we need to print alternate levels in reverse order

#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>

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

vector<vector<int>> zig_zag(Tree_Node* root){
	if(root == nullptr){
		return {};
	}
	vector<vector<int>> ans;
	queue<Tree_Node*> q;

	q.push(root);

	int levelSize;
	int levelIdx = 1;

	while(!q.empty()){
		levelSize = q.size();

		vector<int> level;

		for(int i=0;i<levelSize;i++){
			Tree_Node* curr = q.front();
			q.pop();

			level.push_back(curr->val);

			if(curr->left != nullptr){
				q.push(curr->left);
			}
			if(curr->right != nullptr){
				q.push(curr->right);
			}
		}

		if(levelIdx % 2 == 0){
			reverse(level.begin(),level.end());
		}

		ans.push_back(level);

		levelIdx++;
	}

	return ans;
}

int main(){
    Tree_Node* root = new Tree_Node(6);
    root->left = new Tree_Node(9);
    root->right = new Tree_Node(7);
    root->left->left = new Tree_Node(3);
    root->left->right = new Tree_Node(6);
    root->right->left = new Tree_Node(5);
    root->right->right = new Tree_Node(1);

    vector<vector<int>> ans = zig_zag(root);

    for(int i=0;i<ans.size();i++){
        for(int j=0;j<ans[i].size();j++){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}