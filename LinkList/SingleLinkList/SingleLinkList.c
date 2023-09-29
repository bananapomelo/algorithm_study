#include <stdio.h>
#include <stdlib.h>
#include "SingleLinkList.h"

// ����ͷ���, ����ʼ��
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
            // β�巨
            // head->last->next = newNode;
            // head->last = newNode;
            // ͷ�巨
            newNode->next = head->first;
            head->first = newNode;
        }
        head->nodeNum++;
    }
    return head;
}

// ��: �����½�� 
struct ListHead *addNode (struct ListHead *head, ElemType value){
    struct ListNode *newNode = malloc(sizeof(*newNode));
    newNode->value = value;
    newNode->next = NULL;

    // ͷ�巨
    // ����ʱ ͷ���û���κν��
    if (head->nodeNum == 0){
        head->first = newNode;
        head->last = newNode;
    }
    else{ // ͷ����н��
        // ͷ�巨
        newNode->next = head->first;
        head->first = newNode;
        // β�巨
        // head->last->next = newNode;
        // head->last = newNode;
    }
    head->nodeNum++;
    return head;
}

// ɾ: ɾ��Ŀ��ֵ���
struct ListHead *delNode (struct ListHead *head, ElemType value){
    struct ListNode *traceNode = head->first;
    struct ListNode *pre = NULL;

    while (traceNode){
        if (traceNode->value == value){
            // �Ƿ�ֻ��һ�����
            if (head->nodeNum == 1){
                head->first = NULL;
                head->last = NULL;
                free(traceNode);
                traceNode = NULL;
            }
            // �Ƿ���ͷ���
            else if (pre == NULL){
                head->first = head->first->next;
                traceNode->next = NULL;
                free(traceNode);
                traceNode = head->first;
            }
            // �Ƿ���β���
            else if (traceNode == head->last){ 
                head->last = pre;
                head->last->next = NULL;
                free(traceNode);
                traceNode = NULL;
            }
            // �м���
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

// ��: Ѱ�ҷ���originalDataֵ�Ľ��, ��value����ΪtargetData
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

// ��: Ѱ�ҷ���originalDataֵ�Ľ�㲢����, ���ؼ���ֵ
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

// ��ӡ��������
void printNode (struct ListHead *head){
    struct ListNode *node = head->first;
    while (node){
        printf("List Node Value = %d\n", node->value);
        node = node->next;
    }
}

// �ݻ���������
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
