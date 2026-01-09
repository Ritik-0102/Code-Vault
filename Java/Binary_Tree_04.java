
// Sum of nodes in a Binary Tree

public class Binary_Tree_04 {
    public static class Node{
        int data;
        Node left;
        Node right;
        Node(int data){
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }
    
    //Returns sum of all the nodes in a binary tree
    public static int sum(Node root) {
        if(root == null) {
            return 0;
        }
        return root.data + sum(root.left) + sum(root.right);
    }

    public static void main(String[] args) {
        Node root = new Node(1);
        root.left = new Node(2);
        root.right = new Node(3);
        root.left.left = new Node(4);
        root.left.right = new Node(5);
        root.right.left = new Node(6);
        root.right.right = new Node(7);

        System.out.println("Sum of all the nodes in the tree is "+sum(root));

        // Output:
        // Sum of all the nodes in the tree is 21
    }
}
