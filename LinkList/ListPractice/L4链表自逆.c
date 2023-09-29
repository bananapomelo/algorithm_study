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

SHead * reverseList(SHead *unreverse);
SHead *createHead (void);
void printList (SHead *head);
bool destroyList (SHead *head);

int main()
{
    SHead *reversed = createHead();

    printf("\n\n赋初值:\n");
    printList(reversed);

    reversed = reverseList(reversed);
    printf("\n\n自逆后:\n");
    printList(reversed);

    if (destroyList(reversed))
        printf("\n\nList reversed Destroy success ^_^\n");

/* 终端输入以初始化链表
12
34
78
56
23
99
39
98
45
76
0

*/
    return 0;
}


/*
    reverseList: 自逆链表
        @unreverse: 未自逆链表头结点
        @retval: 自逆后的链表头结点
*/
SHead * reverseList(SHead *unreverse){
    SNode *traversal = unreverse->first;
    unreverse->first = NULL;
    unreverse->last = NULL;

    while (traversal){
        SNode *temp = traversal;
        traversal = traversal->next;
        temp->next = NULL;

        if (unreverse->first == NULL){
            unreverse->first = temp;
            unreverse->last = temp;
        }
        else{
            temp->next = unreverse->first;
            unreverse->first = temp;
        }
        printf("\n\n");
        printList(unreverse);
    }
    
    return unreverse;
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






