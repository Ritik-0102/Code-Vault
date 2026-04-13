# Java Collection Framework

## 1. Core Hierarchy
The root of the collection hierarchy begins with the `Iterable` interface, which is extended by the `Collection` interface.

`Collection` branches into three primary sub-interfaces:
- **List**
- **Queue**
- **Set**

---

## 2. Common Collection Methods
The following standard methods are available to interact with these collections:

| Method | Description |
|--------|-------------|
| `add` | Adds an element to the collection |
| `size` | Returns the number of elements |
| `remove` | Removes an element |
| `iterate` | Loops through elements |
| `addAll` | Adds all elements from another collection |
| `removeAll` | Removes all elements that match |
| `clear` | Removes all elements |

---

## 3. Interfaces & Implementations (When to Use What)

### A. List Interface (Ordered Collections)
Use a **List** when you care about the sequence of elements and might need to store duplicates.

| Implementation | When to Use |
|----------------|-------------|
| **ArrayList** | The default choice. Backed by a dynamic array. Excellent for random access (getting an item by index) and reading data. Slower if you frequently insert or delete elements in the middle of the list. |
| **LinkedList** | Backed by a doubly-linked list. Excellent for frequently adding or removing elements, especially at the beginning or end. Poor choice for random access (getting the 500th item requires traversing from the start). |
| **Vector** | A legacy class similar to ArrayList, but it is synchronized (thread-safe). It is generally slower due to locking overhead. Usually avoided in modern Java in favor of ArrayList or explicit concurrency controls. |
| **Stack** | Extends Vector to provide Last-In-First-Out (LIFO) behavior. *Note: Modern Java recommends using Deque (like ArrayDeque) for stack operations instead.* |

---

### B. Queue Interface (FIFO & Processing)
Use a **Queue** when you need to hold elements prior to processing them, typically in a First-In-First-Out manner.

| Implementation | When to Use |
|----------------|-------------|
| **PriorityQueue** | Elements are ordered based on their natural ordering or a provided Comparator. The "highest priority" element is always served first. Great for task scheduling or finding the top 'N' elements. |
| **LinkedList** | Doubles as a basic Queue since it implements the Queue interface. |
| **Deque** (Double Ended Queue) | Allows insertions and removals at both ends. |
| **ArrayDeque** | The recommended implementation for both general queues and stacks. It is faster than Stack when used as a stack, and faster than LinkedList when used as a queue. |

---

### C. Set Interface (Unique Elements)
Use a **Set** when you need to ensure there are absolutely no duplicate items in your collection.

| Implementation | When to Use |
|----------------|-------------|
| **HashSet** | The default choice. Backed by a Hash Table. Offers extremely fast performance for adding, removing, and checking if an item exists. Does not guarantee any specific iteration order. |
| **LinkedHashSet** | Maintains a doubly-linked list across its elements, meaning it preserves the insertion order. Use this when you want HashSet speed but need to remember the order in which items were added. |
| **TreeSet** | Backed by a Red-Black tree. Keeps elements sorted in ascending order (or by a Comparator). Slower than HashSet, but essential when you need your unique elements strictly organized or need to perform range operations (e.g., "get all numbers between 10 and 20"). |

---

### D. Map Interface (Key-Value Pairs)
*Technically not part of the Collection hierarchy, but a foundational part of the framework.* Use a **Map** when you need to look up data based on a unique key (like a dictionary).

| Implementation | When to Use |
|----------------|-------------|
| **HashMap** | The default choice. Extremely fast lookups and inserts. Allows one null key and multiple null values. Does not guarantee order. |
| **LinkedHashMap** | Preserves the insertion order or access order. Great for building cache systems (like an LRU - Least Recently Used cache). |
| **Hashtable** | A legacy, synchronized (thread-safe) Map. Does not allow null keys or values. Modern Java uses ConcurrentHashMap instead for thread-safe maps. |
| **TreeMap** | Keeps the keys sorted. Useful for range queries on keys (e.g., getting all records for dates between January and March). Slower than HashMap for basic lookups. |
