// Priority Queue Implementation Using Vector

#include <iostream>
#include <vector>
#include <algorithm> // Required for heap operations
#include <stdexcept> // Required for exception handling

using namespace std;

class MyPriorityQueue {
private:
    vector<int> data;

public:
    // Insert an element into the priority queue
    void push(int value) {
        // 1. Add the new element to the end of the vector
        data.push_back(value);
        
        // 2. Rearrange the vector so it remains a valid max-heap
        push_heap(data.begin(), data.end());
    }

    // Remove the highest priority (largest) element
    void pop() {
        if (empty()) {
            throw out_of_range("Cannot pop from an empty priority queue.");
        }
        
        // 1. Move the largest element (at the front) to the back of the vector
        // and restore the heap property for the remaining elements
        pop_heap(data.begin(), data.end());
        
        // 2. Remove that largest element from the vector entirely
        data.pop_back();
    }

    // Access the highest priority element
    int top() const {
        if (empty()) {
            throw out_of_range("Priority queue is empty.");
        }
        // In a max-heap, the largest element is always at index 0 (the front)
        return data.front();
    }

    // Check if the priority queue is empty
    bool empty() const {
        return data.empty();
    }

    // Get the current number of elements
    size_t size() const {
        return data.size();
    }
};

int main() {
    MyPriorityQueue pq;

    // Pushing elements
    pq.push(15);
    pq.push(10);
    pq.push(30);
    pq.push(5);

    cout << "Priority Queue size: " << pq.size() << "\n";
    cout << "Elements in descending (priority) order: ";

    // Popping and printing elements
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    
    // Output: 30 15 10 5
    cout << "\n";

    return 0;
}