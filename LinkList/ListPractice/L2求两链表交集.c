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

SHead *commonOfLists(SHead *listA, SHead *listB);
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

    SHead *commonList = commonOfLists(unSortedListA, unSortedListB);
    printf("交集链表:\n");
    printList(commonList);
    printf("\n\n");

    if (destroyList(unSortedListA))
        printf("List A Destroy success ^_^\n");
    if (destroyList(unSortedListB))
        printf("List B Destroy success ^_^\n");
    if (destroyList(commonList))
        printf("commonList Destroy success ^_^\n");
/* 终端输入以初始化两个链表
2
2
3
4
7
8
0
1
2
2
4
8
9
0

*/
    return 0;
}


/*
    commonOfLists: 求链表的交集, 并且无重复元素
        @listA: 链表A的头指针
        @listB: 链表B的头指针
        @retval: 两链表之间的交集链表的头指针
*/
SHead *commonOfLists(SHead *listA, SHead *listB){
    SHead *intersect = malloc(sizeof(*intersect));
    intersect->first = NULL;
    intersect->last = NULL;
    intersect->nodeNums = 0;

    SNode *moveA = listA->first;
    SNode *moveB = listB->first;

    ElemType diff = 65536;

    // 快慢指针
    while (moveA && moveB){
        // A比B小, A走
        if (moveA->value < moveB->value){
            moveA = moveA->next;
        }
        // B比A小, B走
        else if (moveB->value < moveA->value){
            moveB = moveB->next;
        }
        // A和B相等
        else{
            // 判断是否是重复元素, diff表示上一次存的元素
            if (moveA->value != diff){
                SNode *newNode = malloc(sizeof(*newNode));
                newNode->next = NULL;
                newNode->value = moveA->value;

                if (intersect->nodeNums == 0){
                    intersect->first = newNode;
                    intersect->last = newNode;
                }
                else{
                    intersect->last->next = newNode;
                    intersect->last = newNode;
                }

                intersect->nodeNums++;
                diff = moveA->value;

            }
            moveA = moveA->next;
            moveB = moveB->next;
        }

    }

    return intersect;
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






