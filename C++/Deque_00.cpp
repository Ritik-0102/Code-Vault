// Deque By STL

#include<iostream>
#include<deque>

using namespace std;

int main(){
    deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_back(4);
    
    cout << d.front() << endl;
    cout << d.back() << endl;
    
    d.pop_front();
    d.pop_back();
    
    while (!d.empty()) {
        cout << d.front() << " ";
        d.pop_front();
    }
    cout << endl;
    
    return 0;
}