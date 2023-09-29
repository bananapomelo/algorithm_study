#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int ElemType;

typedef struct SortHead{
    struct SortNode *first;
    struct SortNode *last;
    int nodeNums;
}SHead;

typedef struct SortNode{
    ElemType value;
    struct SortNode *next;
}SNode;

SHead *mergeTwoLists(SHead *listA, SHead *listB);
SHead *createHead (void);
void printList (SHead *head);
bool destroyList (SHead *head);

int main()
{
    SHead *unSortedListA = createHead();
    SHead *unSortedListB = createHead();

    printf("待归并链表A:\n");
    printList(unSortedListA);
    printf("\n\n");

    printf("待归并链表B:\n");
    printList(unSortedListB);
    printf("\n\n");

    SHead *sortedList = mergeTwoLists(unSortedListA, unSortedListB);
    printf("归并后链表:\n");
    printList(sortedList);
    printf("\n\n");

    if (destroyList(unSortedListA))
        printf("List A Destroy success ^_^\n");
    if (destroyList(unSortedListB))
        printf("List B Destroy success ^_^\n");
    if (destroyList(sortedList))
        printf("sortedList Destroy success ^_^\n");
/* 终端输入以初始化两个链表
1
2
4
5
7
0
3
6
8
9
0

*/
    return 0;
}


/*
    mergeTwoLists: 归并两个链表, 合并后仍保持有序
        @listA: 待归并链表A的头指针
        @listB: 待归并链表B的头指针
        @retval: 归并后的有序链表头指针
*/
SHead *mergeTwoLists(SHead *listA, SHead *listB){
    SHead *sortedList = malloc(sizeof(*sortedList));
    sortedList->first = NULL;
    sortedList->last = NULL;
    sortedList->nodeNums = 0;

    while (listA->first && listB->first){
        SNode *newNode = NULL;
        if (listA->first->value < listB->first->value){
            newNode = listA->first;
            listA->first = listA->first->next;
            listA->nodeNums--;
        }
        else{
            newNode = listB->first;
            listB->first = listB->first->next;
            listB->nodeNums--;
        }

        newNode->next = NULL;
        if (sortedList->nodeNums == 0){
            sortedList->first = newNode;
        }
        else{
            sortedList->last->next = newNode;
        }
        sortedList->last = newNode;
        sortedList->nodeNums++;
    }

    if (listA->first){
        sortedList->last->next = listA->first;
        listA->first = listA->last->next; // 使listA = NULL
        sortedList->nodeNums = sortedList->nodeNums + listA->nodeNums;
        listA->nodeNums = 0;
    }
    if (listB->first){
        sortedList->last->next = listB->first;
        listB->first = listB->last->next; // 使listB = NULL
        sortedList->nodeNums = sortedList->nodeNums + listB->nodeNums;
        listB->nodeNums = 0;
    }

    return sortedList;
}
/* 
    createHead: 创建单向有序链表头, 并赋初值
        @retval: 表头指针
*/
SHead *createHead (void){
    SHead *newHead = malloc(sizeof(*newHead));
    newHead->first = NULL;
    newHead->last = NULL;
    newHead->nodeNums = 0;

    while (1){
        SNode *newNode = malloc(sizeof(*newNode));
        ElemType inValue = 0;
        scanf("%d", &inValue);
        if (inValue == 0)
            break;

        newNode->value = inValue;
        newNode->next = NULL;
        // STEP1: 判断是否是空链表
        if (newHead->nodeNums == 0){
            newHead->first = newNode;
            newHead->last = newNode;
        }
        else{
            SNode *traversal = newHead->first;
            SNode *prior = NULL;
            
            int insertFlag = 0;
            while(traversal){
                // 找到第一个比新结点大的结点, 插入到traversal前面
                if (traversal->value > newNode->value){
                    newNode->next = traversal;
                    // 判断找到的结点是否是第一个结点。
                    if(prior == NULL)
                        newHead->first = newNode;
                    else
                        prior->next = newNode; 
                    insertFlag = 1;
                    break;
                }
                prior = traversal;
                traversal = traversal->next;
            }
            //没找到的情况
            if (insertFlag == 0){
                newHead->last->next = newNode;
                newHead->last = newNode;
            }
        }
        newHead->nodeNums += 1;
        
    }
    return newHead;
}

/*
    printList: 打印整个链表
        @head: 链表头指针
*/
void printList (SHead *head){
    SNode *traversal = head->first;
    while (traversal){
        printf("Single Sort Link List Value = %d\n", traversal->value);
        traversal = traversal->next;
    }
}

/*
    desrtoyList: 销毁链表
        @head: 链表头指针
        @retval: 是否成功销毁
*/
bool destroyList (SHead *head){
    SNode *delNode = head->first;
    while (delNode){
        head->first = head->first->next;
        delNode->next = NULL;
        free(delNode);
        delNode = head->first;
        head->nodeNums--;
    }
    if (head->nodeNums == 0 && head->first == NULL){
        head->last = NULL;
        free(head);
    }
    else
        return false;
    return true;
}






