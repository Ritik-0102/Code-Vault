/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    unsigned long long list_to_number(ListNode* l1){
        string s="";
        while(l1!=nullptr){
            string ch=to_string(l1->val);
            s+=ch;
            l1=l1->next;
        }

        reverse(s.begin(),s.end());
        
        unsigned long long num = stoull(s);

        return num;
    }

    ListNode* number_to_list(unsigned long long num){
        if (num == 0) return new ListNode(0);

        ListNode* res=new ListNode(0);

        ListNode* temp = res;
        while(num>0){
            ListNode* newnode = new ListNode(num%10);
            temp->next=newnode;
            temp=temp->next;
            num/=10; 
        }

        return res->next;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        unsigned long long num1=list_to_number(l1);
        unsigned long long num2=list_to_number(l2);

        return number_to_list(num1 + num2);
    }
};