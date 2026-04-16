// Reverse a linked list

class Node{
    int val;
    Node next;

    Node(int data){
        this.val=data;
        this.next=null;
    }
}

class Linked_List{
    Node head;
    

    public void Add(int data){
        Node new_Node=new Node(data);
        if(head==null){
            head=new_Node;
            return;
        }

        Node curr=head;
        while(curr.next!=null){
            curr=curr.next;
        }
        curr.next=new_Node;
        return;
    }


    public void Reverse_LL_Iterative(){
        Node prev=head;
        Node curr=head.next;
        while(curr!=null){
            Node next=curr.next;
            curr.next=prev;
            prev=curr;
            curr=next;
        }
        head.next=null;
        head=prev;
    }

    // Recursive Method
    public Node Reverse_LL_Recursive(Node head) {
        // 1. Base case: if head is null or we reach the last node
        if (head == null || head.next == null) {
            return head; 
        }

        // 2. Recursively reverse the rest of the list
        // newHead will eventually hold the very last node (which becomes the new first node)
        Node newHead = Reverse_LL_Recursive(head.next);

        // 3. Reverse the pointer of the next node to point back to the current node
        head.next.next = head;

        // 4. Break the forward pointer of the current node to prevent cycles
        head.next = null;

        // 5. Return the new head up the call stack
        return newHead;
    }


    public void Print_LL(){
        Node curr=head;
        while(curr!=null){
            System.out.print(curr.val + " -> ");
            curr=curr.next;
        }
        System.out.print("Null");
        System.out.println();
    }
}

public class Linked_List_02 {

    public static void main(String[] args){
        Linked_List list=new Linked_List();

        list.Add(0);
        list.Add(1);
        list.Add(2);
        list.Add(3);
        list.Add(4);
        list.Add(5);

        list.Print_LL();

        list.Reverse_LL_Iterative();

        list.Print_LL();

        list.head=list.Reverse_LL_Recursive(list.head);

        list.Print_LL();
    }
}
