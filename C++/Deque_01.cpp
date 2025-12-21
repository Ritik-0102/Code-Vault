// Deque Implementation Using Doubly Linked List

#include<iostream>

using namespace std;

class Node {
    public:
        int data;
        Node* prev;
        Node* next;
        
        Node(int data) {
            this->data = data;
            this->prev = nullptr;
            this->next = nullptr;
        }
};

class Deque {
    private:
        Node* front;
        Node* rear;
        
    public:
        Deque() {
            this->front = nullptr;
            this->rear = nullptr;
        }
        
        void pushFront(int data) {
            Node* newNode = new Node(data);
            
            if (this->front == nullptr) {
                this->front = newNode;
                this->rear = newNode;
            }
            else {
                newNode->next = this->front;
                this->front->prev = newNode;
                this->front = newNode;
            }
        }
        void pushBack(int data) {
            Node* newNode = new Node(data);
            
            if (this->rear == nullptr) {
                this->front = newNode;
                this->rear = newNode;
            }
            else {
                newNode->prev = this->rear;
                this->rear->next = newNode;
                this->rear = newNode;
            }
        }
        int popFront() {
            if (this->front == nullptr) {
                return -1;
            }
            
            int data = this->front->data;
            
            if (this->front == this->rear) {
                this->front = nullptr;
                this->rear = nullptr;
            }
            else {
                this->front = this->front->next;
                this->front->prev = nullptr;
            }
            
            delete this->front;
            this->front = nullptr;
            
            return data;
        }
        int popBack() {
            if (this->rear == nullptr) {
                return -1;
            }
            
            int data = this->rear->data;
            
            if (this->front == this->rear) {
                this->front = nullptr;
                this->rear = nullptr;
            }
            else {
                this->rear = this->rear->prev;
                this->rear->next = nullptr;
            }
            
            delete this->rear;
            this->rear = nullptr;
            
            return data;
        }
        bool isEmpty() {
            return (this->front == nullptr);
        }
        int getFront() {
            if (this->front == nullptr) {
                return -1;
            }
            
            return this->front->data;
        }
        int getRear() {
            if (this->rear == nullptr) {
                return -1;
            }
            
            return this->rear->data;
        }
};

int main(){
    Deque d;
    d.pushFront(1);
    d.pushFront(2);
    d.pushFront(3);
    d.pushBack(4);
    d.pushBack(5);
    
    cout << d.getFront() << endl;
    cout << d.getRear() << endl;
    
    cout << d.popFront() << endl;
    cout << d.popBack() << endl;
    
    while (!d.isEmpty()) {
        cout << d.popFront() << " ";
    }
    cout << endl;
    
    return 0;
}