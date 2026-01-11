// Sub-tree of a Binary Tree



public class Binary_Tree_06 {
    public static class Node{
        int val;
        Node left;
        Node right;
        Node(int data){
            this.val = data;
            this.left = null;
            this.right = null;
        }
    }
   
   //Returns true if the given tree is a subtree of the original tree
    public static boolean isIdentical(Node root, Node subRoot){
        if(subRoot == null && root == null){
            return true;
        }
        if(root == null || subRoot == null){
            return false;
        }
        if(root.val == subRoot.val){
            return isIdentical(root.left, subRoot.left) && isIdentical(root.right, subRoot.right);
        }
        return false;
    }
    
    public static boolean isSubtree(Node root, Node subRoot){
        if(subRoot == null){
            return true;
        }
        if(root == null){
            return false;
        }
        if(isIdentical(root, subRoot)){
            return true;
        }
        return isSubtree(root.left, subRoot) || isSubtree(root.right, subRoot);
    }


    public static void main(String[] args) {
        Node root = new Node(1);
        root.left = new Node(2);
        root.right = new Node(3);
        root.left.left = new Node(4);
        root.left.right = new Node(5);
        root.right.left = new Node(6);
        root.right.right = new Node(7);

        Node subRoot = new Node(2);
        subRoot.left = new Node(4);
        subRoot.right = new Node(5);

        System.out.println("Is the tree "+subRoot+" a subtree of the original tree? "+isSubtree(root, subRoot));

        // Output:
        // Is the tree [2, 4, 5] a subtree of the original tree? true
    }
}
