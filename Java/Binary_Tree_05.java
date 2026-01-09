// Diameter of a Binary Tree

public class Binary_Tree_05 {
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

    // Approach 1 : O(N^2)
    public static int height(Node root) {
        if(root == null) {
            return 0;
        }
        int leftHeight = height(root.left);
        int rightHeight = height(root.right);
        return 1 + Math.max(leftHeight, rightHeight);
    }

    public static int diameter(Node root) {
       if(root == null) {
           return 0;
       }


       int diam1 = height(root.left) + height(root.right);
       int diam2 = diameter(root.left);
       int diam3 = diameter(root.right);


       return Math.max(diam1, Math.max(diam2, diam3));
    }


    // Approach 2 : O(N)
    static int maxDiameter = 0;

    public static int height_2(Node root) {
        if(root == null) {
            return 0;
        }
        int leftHeight = height_2(root.left);
        int rightHeight = height_2(root.right);
        maxDiameter = Math.max(maxDiameter,leftHeight+rightHeight);
        return 1 + Math.max(leftHeight, rightHeight);
    }
    
    public static int diameter_2(Node root) {
       maxDiameter = 0;
       height_2(root);
       return maxDiameter;
    }

    public static void main(String[] args) {
        Node root = new Node(1);
        root.left = new Node(2);
        root.right = new Node(3);
        root.left.left = new Node(4);
        root.left.right = new Node(5);
        root.right.left = new Node(6);
        root.right.right = new Node(7);

        System.out.println("Diameter of the tree is "+diameter(root));
        System.out.println("Diameter of the tree is "+diameter_2(root));

        // Output:
        // Diameter of the tree is 4
    }

}
