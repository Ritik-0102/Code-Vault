// Linked List Implementation

class Linked_List {
    Node head;
    int size;

    class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    public void Add_First(int data) {
        size++;
        Node newNode = new Node(data);
        if (head == null) {
            head = newNode;
            return;
        }
        newNode.next = head;
        head = newNode;
    }

    public void Add_Last(int data) {
        size++;
        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
            return;
        }
        
        Node curr = head;
        while (curr.next != null) {
            curr = curr.next;
        }
        curr.next = newNode;
    }

    public void addInMiddle(int index, int data) {
        if (index > size || index < 0) {
            System.out.println("Invalid Index value");
            return;
        }
        
        Node newNode = new Node(data);
        if (head == null || index == 0) {
            newNode.next = head;
            head = newNode;
            size++;
            return;
        }
        
        Node currNode = head;
        // Loop stops at index - 1 to insert after it
        for (int i = 1; i < index; i++) {
            currNode = currNode.next;
        }
        
        newNode.next = currNode.next;
        currNode.next = newNode;
        size++;
    }

    public void Remove_First() {
        if (head == null) {
            System.out.println("List is empty");
            return;
        }
        size--;
        head = head.next; // Simply move the head to the next node
    }

    public void Remove_Last() {
        if (head == null) {
            System.out.println("List is empty");
            return;
        }
        
        size--;
        
        // If there's only one node in the list
        if (head.next == null) {
            head = null;
            return;
        }

        Node curr = head;
        // Stop at the SECOND TO LAST node
        while (curr.next.next != null) {
            curr = curr.next;
        }
        // Disconnect the last node
        curr.next = null;
    }

    public void Print_Linked_List() {
        if (head == null) {
            System.out.println("List is empty");
            return;
        }

        Node curr = head;
        while (curr != null) {
            System.out.print(curr.data + " -> ");
            curr = curr.next;
        }
        System.out.println("NULL");
    }
}

public class Linked_List_00 {
    public static void main(String[] args) {
        Linked_List list = new Linked_List();

        list.Add_First(1);
        list.Add_First(2);
        list.Add_First(3);
        list.Add_First(4);
        list.Add_First(5);

        // Expected: 5 -> 4 -> 3 -> 2 -> 1 -> NULL
        list.Print_Linked_List(); 

        // Expected: 4 -> 3 -> 2 -> 1 -> NULL
        list.Remove_First(); 
        list.Print_Linked_List();

        // Expected: 4 -> 3 -> 2 -> NULL
        list.Remove_Last(); 
        list.Print_Linked_List();

        // Expected: 5 -> 4 -> 3 -> 2 -> NULL
        list.Add_First(5);
        list.Print_Linked_List();

        // Expected: 5 -> 4 -> 3 -> 2 -> 1 -> NULL
        list.addInMiddle(4, 1);
        list.Print_Linked_List();
    }
}