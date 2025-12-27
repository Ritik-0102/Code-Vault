// Priority Queue By STL

// it is by default a max priority queue
// implemented using heap

#include<iostream>
#include<queue>

using namespace std;

int main(){
    // Declaration of a Max-Heap priority queue
    priority_queue<int> pq;

    // Inserting elements
    pq.push(10);
    pq.push(30);
    pq.push(20);
    pq.push(5);

    cout << "Max-Heap elements in priority order: ";
    
    // Printing and popping elements
    while (!pq.empty()) {
        cout << pq.top() << " "; // Access the largest element
        pq.pop();                     // Remove it
    }
    
    // Output: 30 20 10 5


    // Declaration of a Min-Heap priority queue
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

    // Inserting elements
    min_pq.push(10);
    min_pq.push(30);
    min_pq.push(20);
    min_pq.push(5);

    std::cout << "Min-Heap elements in priority order: ";
    
    // Printing and popping elements
    while (!min_pq.empty()) {
        std::cout << min_pq.top() << " "; // Access the smallest element
        min_pq.pop();                     // Remove it
    }
    
    // Output: 5 10 20 30
    return 0;
}