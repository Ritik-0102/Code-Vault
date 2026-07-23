// Reverse The elements of Queue

#include<iostream>
#include<queue>
#include<stack>

using namespace std;

// 1st method : Using Stack
void reverseQueue1(queue<int>& q) {
        std::stack<int> s;
        
        // Step 1: Empty the queue into the stack
        while (!q.empty()) {
            s.push(q.front());
            q.pop();
        }
        
        // Step 2: Empty the stack back into the queue
        while (!s.empty()) {
            q.push(s.top());
            s.pop();
        }
    }

// 2nd method : Using Recursion (using call stack)
void reverseQueue2(std::queue<int>& q) {
        // Base case: if the queue is empty, stop recursion
        if (q.empty()) {
            return;
        }
        
        // Step 1: Store the front element and remove it
        int frontElement = q.front();
        q.pop();
        
        // Step 2: Recursively reverse the remaining queue
        reverseQueue2(q);
        
        // Step 3: Enqueue the stored element at the back
        q.push(frontElement);
    }

int main(){
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    
    reverseQueue1(q);
    
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
    reverseQueue2(q);
    
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
}