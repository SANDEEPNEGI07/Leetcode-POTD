// 3217. Delete Nodes From Linked List Present in Array

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> st(nums.begin(),nums.end());
        ListNode* curr=head;
        ListNode* prev=NULL;
        while(curr){
        if(st.count(curr->val)){
            if(prev==NULL){
                head=head->next; //jab head hi dlt krna ho
                curr=head;
            }else {
                prev->next=curr->next;
                curr=curr->next;
                
            }
        }
        else{
            prev=curr;
            curr=curr->next;
        }
    }
        return head;
    }
};