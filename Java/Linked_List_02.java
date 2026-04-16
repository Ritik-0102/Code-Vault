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

public class A {

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
    }
}
