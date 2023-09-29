#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "CircleLinkListWithHead.h"


/*
    createList: 创建单向循环有序链表, 从小到大
        @retval: 链表头指针
*/
CSHead *createList(){
    CSHead *head = malloc(sizeof(*head));
    head->first = NULL;
    head->last = NULL;
    head->nodeNums = 0;

    while (1){
        ElemType inValue = 0;
        scanf("%d", &inValue);
        if (inValue == 0)
            break;
        
        CSNode *newNode = malloc(sizeof(*newNode));
        newNode->next = NULL;
        newNode->value = inValue;

        // Step1: 链表中没有结点
        if (head->nodeNums == 0){
            head->first = newNode;
            head->last = newNode;
            newNode->next = head->first;
        }
        else{
            CSNode *traversal = head->first;
            CSNode *prev = NULL;
            int insertFlag = 0;
            while (1){
                // Step2: 找到第一个比新结点大的结点
                if (traversal->value > newNode->value){
                    // Step2.1: 是头结点情况
                    if (traversal == head->first){
                        newNode->next = traversal;
                        head->first = newNode;
                        head->last = head->first;
                    }
                    // Step2.2: 是中间结点情况
                    else{
                        prev->next = newNode;
                        newNode->next = traversal;
                    }

                    insertFlag = 1;
                    break;
                }
                prev = traversal;
                traversal = traversal->next;
                if (traversal == head->first)
                    break;
            }
            // Step3: 没找到, 插入尾部
            if (insertFlag == 0){
                head->last->next = newNode;
                head->last = newNode;
                newNode->next = head->first;
            }

        }

        head->nodeNums++;
    }

    return head;
}

/*
    addNode: 添加新结点
        @head: 链表头指针 
        @value: 新结点的值
        @retval: 链表头指针
*/
CSHead *addNode(CSHead *head, ElemType value){
    CSNode *newNode = malloc(sizeof(*newNode));
    newNode->value = value;
    newNode->next = NULL;

    // Step1: 链表中无结点
    if (head->nodeNums == 0){
        head->first = newNode;
        head->last = newNode;
        head->last->next = head->first;
    }

    CSNode *traversal = head->first;
    CSNode *prev = NULL;
    int insertFlag = 0;
    while (traversal){
        // Step2: 找到第一个比新结点大的结点
        if (traversal->value > newNode->value){
            // Step2.1: 是头结点
            if (traversal == head->first){
                newNode->next = traversal;
                head->first = newNode;
                head->last->next = head->first;
            }
            // Step2.2: 是中间结点
            else{
                newNode->next = traversal;
                prev->next = newNode;
            }
            insertFlag = 1;
            break;
        }
        prev = traversal;
        traversal = traversal->next;
        if (traversal == head->first)
            break;
    }
    // Step3: 是尾结点
    if (insertFlag == 0){
        head->last->next = newNode;
        head->last = newNode;
        head->last->next = head->first;
    }

    head->nodeNums++;
    return head;
}

/*
    delNode: 删除结点
        @head: 链表头结点
        @value: 待删除的结点值
        @retval: 链表头结点
*/
CSHead *delNode(CSHead *head, ElemType value){
    CSNode *traversal = head->first;
    CSNode *prev = NULL;
    while(traversal){
        // Step1: 找到待删除的结点
        if (traversal->value == value){
            // Step2: 链表中只有一个结点
            if (head->nodeNums == 1){
                traversal->next = NULL;
                head->first = NULL;
                head->last = NULL;
                free(traversal);
                traversal = head->first;
            }
            // Step3: 是头结点
            else if (traversal == head->first){
                head->first = head->first->next;
                head->last->next = head->first;
                traversal->next = NULL;
                free(traversal);
                traversal = head->first;
            }
            // Step4: 是尾结点
            else if (traversal == head->last){
                head->last = prev;
                head->last->next = head->first;
                traversal->next = NULL;
                free(traversal);
                traversal = head->last;
            }
            // Step5: 是中间结点
            else{
                prev->next = traversal->next;
                traversal->next = NULL;
                free(traversal);
                traversal = prev;
            }

            head->nodeNums--;
        }
        prev = traversal;
        traversal = traversal->next;
        if (traversal == head->first)
            break;
    }
    return head;
}

/*
    insertSort: 单向循环链表的插入排序
        @head: 链表头结点
        @retval: 链表头结点
*/
CSHead *insertSort(CSHead *head){
    if (head->first == NULL || head->first->next == NULL)
        return head;
    

    CSNode *sortedNode = head->first;
    CSNode *unsortedNode = sortedNode->next;

    sortedNode->next = NULL; // 初始化已排序链表，只包含第一个节点

    while (unsortedNode != NULL && unsortedNode != sortedNode){
        // 当前节点应插入到sortedNode的头部
        CSNode *current = unsortedNode;
        unsortedNode = unsortedNode->next;
        
        if (current->value < sortedNode->value){
            current->next = sortedNode;
            sortedNode = current;
        }
        else{
            // 在sortedNode中找到正确的插入位置
            CSNode *temp = sortedNode;
            while (temp != NULL && temp->next != NULL && temp->next->value < current->value)
                temp = temp->next;
            
            current->next = temp->next;
            temp->next = current;
        }
    }

    // 使头指针的first和last指向正确位置
    CSNode *lastFlag = sortedNode;
    while(lastFlag->next)
        lastFlag = lastFlag->next;

    head->first = sortedNode;
    head->last = lastFlag;
    head->last->next = head->first;

    return head;
}


/*
    changeNode: 修改结点的值, 并对结点进行排序
        @head: 链表头指针
        @sourceData: 带搜索的目标结点值
        @targetData: 修改后的结点值
        @retval: 链表头指针
*/
CSHead *changeNode(CSHead *head, ElemType sourceData, ElemType targetData){
    CSNode *traversal = head->first;
    while (traversal){
        if (traversal->value == sourceData)
            traversal->value = targetData;
        traversal = traversal->next;
        if (traversal == head->first)
            break;
    }
    printf("修改后: \n");
    printList(head);
    printf("\n\n");
    // 排序算法
    head = insertSort(head);
    printf("dasf");
    return head;
}

/*
    searchNode: 搜索符合目标值的结点数量
        @head: 链表头指针
        @value: 带搜索的结点值
        @retval: 符合目标值的结点数量
*/
int searchNode(CSHead *head, ElemType value){
    int equalFlag = 0;
    CSNode *traversal = head->first;
    while (traversal){
        if (traversal->value == value)
            equalFlag++;
        traversal = traversal->next;
        if (traversal == head->first)
            break;
    }
    return equalFlag;
}

/*
    printList: 打印整个链表
        @head: 链表头指针
*/
void printList(CSHead *head){
    CSNode *traversal = head->first;
    while (traversal){
        printf("Circle Link List With Head Value: %d\n", traversal->value);
        traversal = traversal->next;
        if (traversal == head->first)
            break;
    }
}

/*
    proveCircle: 验证该链表是否是循环链表
        @head: 链表头指针
*/
void proveCircle(CSHead *head){
    CSNode *traversal = head->first;
    while (traversal){
        printf("Circle Link List With Head Value: %d\n", traversal->value);
        traversal = traversal->next;
        if (traversal == head->first){
            sleep(2);
            printf("\n\n");
        }
    }
}

/*
    destroyList: 销毁链表
        @head: 链表头指针
        @retval: 返回是否销毁成功
*/
bool destroyList(CSHead *head){
    CSNode *traversal = head->first;
    while (traversal){
        head->first = head->first->next;
        traversal->next = NULL;
        free(traversal);
        head->nodeNums--;
        if (head->nodeNums == 0){
            head->first = NULL;
            head->last = NULL;
        }
        traversal = head->first;
    }
    return true;
}
