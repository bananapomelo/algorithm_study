#include <stdio.h>
#include <stdlib.h>
#include "SingleLinkList.h"

// 创建头结点, 并初始化
struct ListHead *createList (void){
    struct ListNode *newNode = NULL;

    struct ListHead *head = malloc(sizeof(*head));
    head->first = NULL;
    head->last = NULL;
    head->nodeNum = 0;

    while (1){
        int nodeValue = 0;
        scanf("%d", &nodeValue);
        if (nodeValue == 0)
            break;
        
        newNode = malloc(sizeof(*newNode));
        newNode->next = NULL;
        newNode->value = nodeValue;

        if (head->nodeNum == 0){
            head->first = newNode;
            head->last = newNode;
        }
        else{
            // 尾插法
            // head->last->next = newNode;
            // head->last = newNode;
            // 头插法
            newNode->next = head->first;
            head->first = newNode;
        }
        head->nodeNum++;
    }
    return head;
}

// 增: 增加新结点 
struct ListHead *addNode (struct ListHead *head, ElemType value){
    struct ListNode *newNode = malloc(sizeof(*newNode));
    newNode->value = value;
    newNode->next = NULL;

    // 头插法
    // 插入时 头结点没有任何结点
    if (head->nodeNum == 0){
        head->first = newNode;
        head->last = newNode;
    }
    else{ // 头结点有结点
        // 头插法
        newNode->next = head->first;
        head->first = newNode;
        // 尾插法
        // head->last->next = newNode;
        // head->last = newNode;
    }
    head->nodeNum++;
    return head;
}

// 删: 删除目标值结点
struct ListHead *delNode (struct ListHead *head, ElemType value){
    struct ListNode *traceNode = head->first;
    struct ListNode *pre = NULL;

    while (traceNode){
        if (traceNode->value == value){
            // 是否只有一个结点
            if (head->nodeNum == 1){
                head->first = NULL;
                head->last = NULL;
                free(traceNode);
                traceNode = NULL;
            }
            // 是否是头结点
            else if (pre == NULL){
                head->first = head->first->next;
                traceNode->next = NULL;
                free(traceNode);
                traceNode = head->first;
            }
            // 是否是尾结点
            else if (traceNode == head->last){ 
                head->last = pre;
                head->last->next = NULL;
                free(traceNode);
                traceNode = NULL;
            }
            // 中间结点
            else{
                pre->next = traceNode->next;
                traceNode->next = NULL;
                free(traceNode);
                traceNode = pre;
            }
            head->nodeNum--;
        }
        
        pre = traceNode;
        if(traceNode)
            traceNode = traceNode->next;
    }

    return head;
}

// 改: 寻找符合originalData值的结点, 将value更改为targetData
struct ListHead *changeNode (struct ListHead *head, ElemType originalData, ElemType targetData){
    struct ListNode *newHead = head->first;
    struct ListNode *pre = NULL;
    
    while (newHead){
        if (newHead->value == originalData)
            newHead->value = targetData;

        pre = newHead;
        newHead = newHead->next;
    }

    return head;
}

// 查: 寻找符合originalData值的结点并计数, 返回计数值
int findNode (struct ListHead *head, ElemType originalData){
    int count = 0;

    struct ListNode *newHead = head->first;
    while(newHead){
        if (newHead->value == originalData)
            count++;
        newHead = newHead->next;
    }

    return count;
}

// 打印整个链表
void printNode (struct ListHead *head){
    struct ListNode *node = head->first;
    while (node){
        printf("List Node Value = %d\n", node->value);
        node = node->next;
    }
}

// 摧毁整个链表
void destoryList (struct ListHead *head){
    struct ListNode *node = head->first;
    while(node){
        head->first = head->first->next;
        node->next = NULL;
        free(node);
        node = head->first;
        head->nodeNum--;
    }
    free(head);
    printf("List head destory complete\n");
}
