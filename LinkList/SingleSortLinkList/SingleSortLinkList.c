#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SingleSortLinkList.h"


/* 
    createHead: 创建单向有序链表头, 并赋初值
        @retval: 表头指针
*/
struct SortHead *createHead (void){
    struct SortHead *newHead = malloc(sizeof(*newHead));
    newHead->first = NULL;
    newHead->last = NULL;
    newHead->nodeNums = 0;

    while (1){
        struct SortNode *newNode = malloc(sizeof(*newNode));
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
            struct SortNode *traversal = newHead->first;
            struct SortNode *prior = NULL;
            
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
    addNodeToList: 添加新结点
        @head: 链表头指针
        @value: 新结点的值
        @retval: 添加后的链表头指针
*/
struct SortHead *addNodeToList (struct SortHead *head, ElemType value){
    struct SortNode *newNode = malloc(sizeof(*newNode));
    newNode->value = value;
    newNode->next = NULL;

    if (head->nodeNums == 0){
        head->first = newNode;
        head->last = newNode;
    }

    struct SortNode *traversal = head->first;
    struct SortNode *prior = NULL;
    int insertFlag = 0;
    while (traversal){
        if (traversal->value > newNode->value){
            if (prior == NULL){
                newNode->next = head->first;
                head->first = newNode;
            }
            else{
                newNode->next = traversal;
                prior->next = newNode;
            }
            insertFlag++;
            break;
        }
        prior = traversal;
        traversal = traversal->next;
    }
    if (insertFlag == 0){
        head->last->next = newNode;
        head->last = newNode;
    }
    head->nodeNums++;
    printList(head);
    printf("\n\n");
    head = bubbleSort(head);
 
    return head;
}

/*
    delNode: 删除结点
        @head: 链表头指针
        @value: 需要删除的结点的值
        @retval: 删除后的链表头指针
*/
struct SortHead *delNode (struct SortHead *head, ElemType value){
    struct SortNode *traversal = head->first;
    struct SortNode *prior = NULL;

    while (traversal){
        if (traversal->value == value){
            if (head->nodeNums == 1){
                head->first = NULL;
                head->last = NULL;
                free(traversal);
                traversal = NULL;
            }
            else if (traversal == head->first){
                head->first = head->first->next;
                traversal->next = NULL;
                free(traversal);
                traversal = head->first;
            }
            else if (traversal == head->last){
                head->last = prior;
                prior->next = NULL;
                free(traversal);
                traversal = NULL;
            }
            else{
                prior->next = traversal->next;
                traversal->next = NULL;
                free(traversal);
                traversal = prior->next;
                head->nodeNums--;
                printf("wocao:%d\n", head->nodeNums);
                continue;
            }
            head->nodeNums--;
            printf("wocao:%d\n", head->nodeNums);
        }
        prior = traversal;
        traversal = traversal->next;
    }

    return head;
}

/*
    bubbleSort: 对链表使用冒泡排序算法
        @head: 链表头指针
        @retval: 排序后的链表头指针

*/
struct SortHead *bubbleSort (struct SortHead *head){
    struct SortNode *prior = NULL;
    struct SortNode *traversal = head->first;
    struct SortNode *forward = traversal->next;

    for (int i = 0; i < head->nodeNums - 1; i++){
        for (int j = 0; j < head->nodeNums - 1 - i; j++){
            // printf("function = %s, line = %d\n", __FUNCTION__, __LINE__);
            if (traversal->value > forward->value){
                traversal->next = forward->next;
                forward->next = traversal;
                if (prior == NULL)
                    head->first = forward;
                else
                    prior->next = forward;
                prior = forward;
                forward = traversal->next;                             
            }
            else{
                prior = traversal;
                traversal = forward;
                if (traversal != head->last)
                    forward = forward -> next;
            }
        }
    }
    return head;
}

/* 
    changeValue: 搜索结点中符合修改条件的, 将其值修改
        @head: 头结点
        @originalData: 待修改结点值
        @targetData: 修改后的值
    注意: 修改结点后, 要对整个链表重新排序
*/
struct SortHead * changeValue (struct SortHead *head, ElemType originalData, ElemType targetData){
    struct SortNode *traversal = head->first;
    while (traversal){
        if (traversal->value == originalData){
            traversal->value = targetData;
        }
        traversal = traversal->next;
    }
    head = bubbleSort(head);

    return head;
}

/*
    searchValue: 搜索符合目标值的链表数量
        @head: 链表头指针
        @targetData: 待搜索结点的值
        @retval: 符合目标值的结点数量
*/
int searchValue (struct SortHead *head, ElemType targetData){
    struct SortNode *traversal = head->first;
    int searchCount = 0;
    while (traversal){
        if (traversal->value == targetData)
            searchCount++;

        traversal = traversal->next;
    }
    
    return searchCount;
}

/*
    printList: 打印整个链表
        @head: 链表头指针
*/
void printList (struct SortHead *head){
    struct SortNode *traversal = head->first;
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
bool destroyList (struct SortHead *head){
    struct SortNode *delNode = head->first;
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







