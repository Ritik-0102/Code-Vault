// Tower of Hanoi

// We need to move n disks from source to destination

// Rules :-
// 1. Only one disk can be moved in 1 step
// 2. Smaller disks are always kept on top of larger disks

// Algorithm :-
// 1. Move n-1 disks from source to helper
// 2. Move 1 disk from source to destination
// 3. Move n-1 disks from helper to destination

#include<iostream>
#include<vector>

using namespace std;

void TowerOfHanoi(int n, string source, string helper, string destination){
    if (n == 1){
        cout << "Move disk 1 from " << source << " to " << destination << endl;
        return;
    }

    TowerOfHanoi(n - 1, source, destination, helper);
    cout << "Move disk " << n << " from " << source << " to " << destination << endl;
    TowerOfHanoi(n - 1, helper, source, destination);
}

int main(){
    int n;
    cin >> n;
    TowerOfHanoi(n, "A", "B", "C");
    return 0;
}