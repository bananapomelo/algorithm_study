#ifndef __SINGLELINKLIST_H__
#define __SINGLELINKLIST_H__

typedef int ElemType;

struct ListNode{
    ElemType value;
    struct ListNode* next;
};
struct ListHead{
    struct ListNode *first;
	struct ListNode *last;
	int nodeNum;
};

extern struct ListHead *createList (void);
extern struct ListHead *addNode (struct ListHead *head, ElemType value);
extern struct ListHead *delNode (struct ListHead *head, ElemType value);
extern struct ListHead *changeNode (struct ListHead *head, ElemType originalData, ElemType targetData);
extern int findNode (struct ListHead *head, ElemType originalData);
extern void printNode (struct ListHead *head);
extern void destoryList (struct ListHead *head);


#endif