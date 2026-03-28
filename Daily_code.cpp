

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        long long int n1=0,n2=0;
        int i=0,j=0;
        while(l1.next!=NULL){
            n1+=(l1.val)*(pow(10,i));
            i++;
            l1=l1.next;
        }
        while(l2.next!=NULL){
            n2+=(l2.val)*(pow(10,j));
            j++;
            l2=l2.next;
        }

        long long int n3=n1+n2;
        ListNode* res=new ListNode();

        ListNode* temp=res;
        while(n3>0){
            int temp=n3%10;
        }
    }
};