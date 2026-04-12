class Linked_List {
    Node head;

    class Node{
        int data;
        Node next;

        Node(int data){
            this.data=data;
            this.next=null;
        }
    }

    public void Add_First(int data){
        Node newNode=new Node(data);
        if(head==null){
            head=newNode;
            return;
        }

        newNode.next=head;
        head=newNode;
        return;
    }

    public void Add_Last(int Data){
        Node newNode=new Node(Data);

        if(head==null){
            head=newNode;
            return;
        }
        
        Node curr=head;
        while(curr.next!=null){
            curr=curr.next;
        }

        curr.next=newNode;
        return;
    }

    public Node Remove_First(){
        if(head==null || head.next==null){
            return null;
        }

        head=head.next;
        return head;
    }

    public Node Remove_Last(){
        if(head==null || head.next==null){
            return null;
        }

        Node curr=head;
        while(curr.next!=null){
            curr=curr.next;
        }
        curr.next=curr.next.next;
        return head;
    }

    public void Print_Linked_List(){
        if(head==null){
            return;
        }

        Node curr=head;
        while(curr!=null){
            System.out.print(curr.data + " -> ");
            curr=curr.next;
        }
        System.out.println("NULL");
    }
}

class Linked_List_00{

    public static void main(String[] args){
        Linked_List List=new Linked_List();

        List.Add_First(1);
        List.Add_First(2);
        List.Add_First(3);
        List.Add_First(4);
        List.Add_First(5);

        List.Print_Linked_List();

        List.head=List.Remove_First();

        List.Print_Linked_List();

        List.head=List.Remove_Last();

        List.Print_Linked_List();
    }
}
