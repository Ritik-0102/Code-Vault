# 1. The Standard Library Solution: collections.deque

from collections import deque

# Create a deque (Doubly Linked List behavior)
dll = deque([1, 2, 3])

# Append to right (Tail) - O(1)
dll.append(4) 

# Append to left (Head) - O(1)
dll.appendleft(0)

# Pop from right - O(1)
dll.pop()

# Pop from left - O(1)
dll.popleft()

print(dll) # Output: deque([0, 1, 2, 3])



# 2. Custom Implementation of a Doubly Linked List

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        
        last = self.head
        while last.next:
            last = last.next
        last.next = new_node

    def display(self):
        current = self.head
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("None")

# Usage
ll = LinkedList()
ll.append(10)
ll.append(20)
ll.display() 
# Output: 10 -> 20 -> None