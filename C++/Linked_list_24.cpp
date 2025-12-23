// we need to delete array elements from the linked list

// 2 -> 8 -> 3 -> 2 -> 2 -> 9 -> 2 -> NULL
// arr={3,2}

// Step 1. Store all the values of nums array in set
// Step 2. now delete elements from linked list which are present in the set


#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

class ListNode{
    public:
    int val;
    ListNode* next;

    ListNode(int data){
        val=data;
        next=NULL;
    }

    ListNode(int data,ListNode* nextNode){
        val=data;
        next=nextNode;
    }
};

void insert_at_tail(ListNode* &head,int value){
    ListNode* new_node=new ListNode(value);
    
    if(head==NULL){
        head=new_node;
        return;
    }
    
    ListNode* temp=head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=new_node;
}

void print_linked_list(ListNode* head){
    ListNode* temp=head;
    while(temp!=NULL){
        cout << temp->val << " -> ";
        temp=temp->next;
    }
    cout << "NULL" << endl;
}

ListNode* modifiedList(vector<int>& nums, ListNode* head){
    if (head == nullptr){
        return nullptr;
    }

    unordered_set<int> s;
    for (int val : nums){
        s.insert(val);
    }

    // Pro-tip 1: Initialize the set in one line
    // unordered_set<int> s(nums.begin(), nums.end());

    ListNode *DummyNode = new ListNode(0, head);
    ListNode *temp = DummyNode;

    // Pro-tip 2: Allocate DummyNode on the stack to avoid 'new' and 'delete'
    // ListNode DummyNode(0, head); 
    // ListNode* temp = &DummyNode;

    while (temp != nullptr && temp->next != nullptr){
        if (s.find(temp->next->val) != s.end()){
            temp->next = temp->next->next;
        }
        else{
            temp = temp->next;
        }
    }

    return DummyNode->next;
}

int main(){
    vector<int> nums = {3,2};

    ListNode* head = new ListNode(2);
    insert_at_tail(head,3);
    insert_at_tail(head,3);
    insert_at_tail(head,8);
    insert_at_tail(head,3);
    insert_at_tail(head,2);
    insert_at_tail(head,2);
    insert_at_tail(head,9);
    insert_at_tail(head,2);

    head = modifiedList(nums, head);

    print_linked_list(head);

    return 0;
}
