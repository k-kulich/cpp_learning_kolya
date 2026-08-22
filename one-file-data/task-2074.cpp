#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        if (head == nullptr) return nullptr;

        size_t cur_group = 1; // size of group
        
        ListNode* start = head;
        ListNode* curr = head;
        while (curr) {
            ListNode* end = curr;
            int k = 0;  // тут будем считать размер группы
            while (k < cur_group && end) {
                end = end->next;
                ++k;
            }

            if (cur_group % 2 == 0) {
                ListNode* new_head = reverseGroup(curr, end, k);
                start->next = new_head;
                start = curr;  // now it is in the end
            } else {
                ListNode* tail = curr;
                for (int i = 0; i < cur_group - 1; ++i) curr = curr->next;
                start = tail;  // just move start of group
            }

            curr = end;
            ++cur_group;
        }

        return head;
    }

    ListNode* reverseGroup(ListNode* start, ListNode* end, int k) {
        // start - first elem, end - elem after group
        ListNode* prev = end;
        ListNode* curr = start;
        for (int i = 0; i < k; ++i) {
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        // new head is prev now
        return prev;
    }
};
