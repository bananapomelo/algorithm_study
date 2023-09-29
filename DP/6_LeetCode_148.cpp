class Solution {
private:
  ListNode* getMedian(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }
  
  ListNode* mergeSortedList(ListNode* head1, ListNode* head2) {
    if (!head1 || !head2) return head1 ? head1 : head2;

    if (head1->val < head2->val) {
      head1->next = mergeSortedList(head1->next, head2);
      return head1;
    } else {
      head2->next = mergeSortedList(head1, head2->next);
      return head2;
    }
  }

public:
  ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode *mid = getMedian(head);
    ListNode *next = mid->next;
    mid->next = nullptr;

    ListNode *list1 = sortList(head);
    ListNode *list2 = sortList(next);
    return mergeSortedList(list1, list2);
  }
};