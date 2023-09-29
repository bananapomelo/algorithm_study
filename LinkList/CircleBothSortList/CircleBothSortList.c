#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CircleBothSortList.h"


/*
    addNode: 分为两种模式. (1) 插入值(创建新结点) (2) 插入节点
        @head: 链表头指针
        @value: 插入的节点值
        @insert: 是否插入节点, NULL为不插入
        @retval: 链表头指针
*/
CBSHead *addNode(CBSHead *head, ElemType value, CBSNode *insert){
    CBSNode *newNode = NULL;
    // Step1: 按节点插入
    if (insert){
        newNode = insert;
    }
    // Step1.1: 按值插入
    else{
        newNode = malloc(sizeof(*newNode));
        newNode->prev = NULL;
        newNode->next = NULL;
        newNode->value = value;
    }
    
    // Step2: 空链表
    if (head->nodeNums == 0){
        head->first = newNode;
        head->last = newNode;
        newNode->next = head->first;
        newNode->prev = head->last;
    }
    else{
        CBSNode *traversal = head->first;
        int insertFlag = 0;
        while (traversal){
            // Step3: 找到第一个比新节点值大的节点
            if (traversal->value > newNode->value){
                // Step3.1: 是头结点情况
                if (traversal == head->first){
                    newNode->next = traversal;
                    newNode->prev = head->last;
                    head->last->next = newNode;
                    head->first->prev = newNode;
                    head->first = newNode;
                }
                // Step3.2: 是中间结点情况
                else{
                    newNode->next = traversal;
                    newNode->prev = traversal->prev;
                    traversal->prev->next = newNode;
                    traversal->prev = newNode;
                }

                insertFlag = 1;
                break;
            }
            traversal = traversal->next;
            if (traversal == head->first)
                break;
        }

        // Step4: 没找到, 插入链表尾部
        if (insertFlag == 0){
            newNode->next = head->first;
            newNode->prev = head->last;
            head->first->prev = newNode;
            head->last->next = newNode;
            head->last = newNode;
        }
    }
    if (insert == NULL)
        head->nodeNums++;
    return head;
}

/*
    createList: 创建链表并初始化
        @retval: 链表头指针
*/
CBSHead *createList(){
    CBSHead *head = malloc(sizeof(*head));
    head->first = NULL;
    head->last = NULL;
    head->nodeNums = 0;

    while (1){
        ElemType inputValue = 0;
        scanf("%d", &inputValue);

        if(inputValue == 0)
            break;

        head = addNode(head, inputValue, NULL);
    }

    return head;
}

/*
    delNode: 删除符合targetData值的节点
        @head: 链表头指针
        @targetData: 待删除节点值
        @retval: 链表头节点
*/
CBSHead *delNode(CBSHead *head, ElemType targetData){
    if (head->nodeNums == 0)
        return head;

    CBSNode *traversal = head->first;
    
    while (traversal){
        int delFlag = 0;
        if (traversal->value == targetData){
            if (traversal == head->first){
                if (head->nodeNums == 1){
                    head->first = NULL;
                    head->last = NULL;
                }
                else{
                    head->first = head->first->next;
                    head->last->next = head->first;
                    head->first->prev = head->last;
                }
                traversal->next = NULL;
                traversal->prev = NULL;
                free(traversal);
                traversal = head->first;
                delFlag = 1;
            }
            else if (traversal == head->last){
                head->last = head->last->prev;
                head->last->next = head->first;
                head->first->prev = head->last;
                traversal->next = NULL;
                traversal->prev = NULL;
                free(traversal);
                traversal = head->last;
            }
            else {
                CBSNode *temp = traversal->prev;
                temp->next = traversal->next;
                traversal->next->prev = temp;
                traversal->next = NULL;
                traversal->prev = NULL;
                free(traversal);
                traversal = temp;
            }

            head->nodeNums--;
        }

        if (traversal == NULL)
            break;
        if (delFlag == 0)
            traversal = traversal->next;

        if (delFlag == 0 && traversal == head->first)
            break;
    }

    return head;
}

/*
    changeNode: 改变节点值并重新排序
        @head: 链表头指针
        @sourceData: 需要改的节点值
        @targetData: 修改后的节点值
        @retval: 链表头指针
*/
CBSHead *changeNode(CBSHead *head, ElemType sourceData, ElemType targetData){
    if (sourceData == targetData)
        return head;
    
    CBSNode *traversal = head->first;
    int changeFlag = 0;
    while (traversal){
        if (traversal->value == sourceData){
            traversal->value = targetData;
            CBSNode *prev = traversal->prev;
            CBSNode *next = traversal->next;
            
            if (traversal == head->first){
                head->first = head->first->next;
                next->prev = head->last;
                prev->next = head->first;
                traversal->prev = NULL;
                traversal->next = NULL;
            }
            else if (traversal == head->last){
                head->last = prev;
                prev->next = head->first;
                next->prev = head->last;
                traversal->prev = NULL;
                traversal->next = NULL;
            }
            else{
                prev->next = next;
                next->prev = prev;
                traversal->prev = NULL;
                traversal->next = NULL;
            }
            head = addNode(head, 0, traversal);
            traversal = head->first;
            changeFlag = 1;
        }
        if (changeFlag)
            changeFlag = 0;
        else
            traversal = traversal->next;
        if (changeFlag == 0 && traversal== head->first)
            break;
    }
    return head;
}


/*
    searchNode: 搜索符合targetData值的节点个数
        @head: 链表头指针
        @targetData: 待匹配的节点值
        @retval: 节点个数
*/
int searchNode(CBSHead *head, ElemType targetData){
    CBSNode *traversal = head->first;
    int equalNums = 0;
    while (traversal){
        if (traversal->value == targetData)
            equalNums++;

        traversal = traversal->next;
        if (traversal == head->first)
            break;
    }

    return equalNums;
}

/*
    printList: 打印链表
*/
void printList(CBSHead *head){
    CBSNode *traversal = head->first;
    while (traversal){
        printf("Circle Both Sort List Value: %d\n", traversal->value);

        traversal = traversal->next;
        if (traversal == head->first)
            break;
    }
}

/*
    desrtoyList: 销毁链表
        @head: 链表头指针
        @retval: 销毁true or false
*/
bool destroyList(CBSHead *head){
    head->first->prev = NULL;
    head->last->next = NULL;
    CBSNode *traversal = head->first;
    while (traversal){
        head->first = head->first->next;
        if (head->first)
            head->first->prev = NULL;
        traversal->next = NULL;
        free(traversal);
        traversal = head->first;
        head->nodeNums--;
    }
    head->last = NULL;
    
    if (head->first == NULL && head->last == NULL && head->nodeNums == 0)
        return true;
    else
        return false;
}



