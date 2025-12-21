#include<iostream>
#include<vector>

using namespace std;

class MyCircularQueue {
public:
    vector<int> arr;
    int size;
    int capacity;
    int front;
    int rear;
    MyCircularQueue(int k) {
        arr.assign(k,0);
        capacity = k; 
        size = 0;
        front = 0;
        rear = 0;
    }
    
    bool enQueue(int value) {
        if(size < capacity){
            arr[rear] = value;
            rear++;
            size++;
            rear %= capacity;
            return true;
        }
        return false;
    }
    
    bool deQueue() {
        if(size > 0){
            front++;
            size--;
            front %= capacity;
            return true;
        }
        return false;        
    }
    
    int Front() {
        if(size == 0){
            return -1;
        }
        return arr[front];
    }
    
    int Rear() {
        if(size == 0){
            return -1;
        }
        return arr[(rear + capacity - 1) % capacity];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};

int main(){
    MyCircularQueue q(5);
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    q.enQueue(4);
    q.enQueue(5);
    
    cout << q.Front() << endl;
    cout << q.Rear() << endl;
    
    cout << q.deQueue() << endl;
    cout << q.deQueue() << endl;
    cout << q.deQueue() << endl;
    cout << q.deQueue() << endl;
    cout << q.deQueue() << endl;
    
    while (!q.isEmpty()) {
        cout << q.deQueue() << " ";
    }
    cout << endl;
    
    return 0;
}