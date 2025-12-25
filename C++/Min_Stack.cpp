// Design a Min stack

// In this we will be implementing push, pop, top, getMin, and empty operations all in O(1) time

#include<iostream>
#include<stack>

using namespace std;

// Approach 1 : 
// Using a stack to store the value in pair of (value, min)
// Time Complexity : O(1)
// Space Complexity : O(2*n) --> O(n)

class Min_Stack{
    stack<pair<int,int>> s;
    public:
        void push(int x){
            if(s.empty()){
                s.push({x,x});
            }
            else{
                s.push({x,min(x,s.top().second)});
            }
        }

        void pop(){
            s.pop();
        }

        int top(){
            return s.top().first;
        }

        int getMin(){
            return s.top().second;
        }

        bool empty(){
            return s.empty();
        }
};



// Approach 2 : 
// In this we will maintain a minVal variable which will store the minimum value of the stack
// if our current value is smaller than minVal then we will push ( 2 * currVal - minVal)
// And update our minVal with this currVal

// Time Complexity : O(1)
// Space Complexity : O(n)

class Min_Stack_2 {
    stack<int> s;
    int minVal;
    public:
        void push(int x){
            if(s.empty()){
                s.push(x);
                minVal = x;
                return;
            }
            if(x <= minVal){
                s.push(2 * x - minVal);
                minVal = x;
            }
            else{
                s.push(x);
            }
        }
        
        void pop(){
            if(s.empty()){
                return;
            }

            if(s.top() <= minVal){
                minVal = 2*minVal - s.top();
            }
            s.pop();
        }

        int top(){
            if(s.empty()){
                return -1;
            }

            if(s.top() <= minVal){
                return minVal;
            }
            return s.top();
        }

        int getMin(){
            return minVal;
        }

        bool empty(){
            return s.empty();
        }
};

int main(){
    Min_Stack s;
    Min_Stack_2 s2;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);

    cout << s.getMin() << endl;

    s2.push(1);
    s2.push(2);
    s2.push(3);
    s2.push(4);
    s2.push(5);
    s2.push(6);

    cout << s2.getMin() << endl;

    return 0;
}