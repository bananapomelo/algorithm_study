#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BothWayLinkListWithHead.h"

/*
    createList: 创建双向有序链表并初始化
        @retval: 链表头指针
*/
struct BothHead *createList(){
    struct BothHead *head = malloc(sizeof(*head));
    head->first = NULL;
    head->last = NULL;
    head->nodeNums = 0;

    while (1){
        ElemType inputValue = 0;
        scanf("%d", &inputValue);
        if (inputValue == 0)
            break;

        struct BothNode *newNode = malloc(sizeof(*newNode));
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->value = inputValue;
        int insertFlag = 0;


        if (head->nodeNums == 0){
            head->first = newNode;
            head->last = newNode;
        }
        else{
            struct BothNode *traversal = head->first;
            while (traversal){
                if (traversal->value > newNode->value){
                    newNode->next = traversal;
                    if (traversal == head->first){
                        traversal->prev = newNode;
                        head->first = newNode;
                    }
                    else{
                        newNode->prev = traversal->prev;
                        traversal->prev->next = newNode;
                        traversal->prev = newNode;
                    }
                    insertFlag = 1;
                    break;
                }
                traversal = traversal->next;
            }
            if (insertFlag == 0){
                head->last->next = newNode;
                newNode->prev = head->last;
                head->last = newNode;
            }
        }
        
        head->nodeNums++;
    }

    return head;
}

/*
    addNodeToList: 添加结点到链表中
        @head: 链表头指针
        @value: 插入的值
        @retval: 链表头指针
*/
struct BothHead *addNode(struct BothHead *head, ElemType value){
    struct BothNode *newNode = malloc(sizeof(*newNode));
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->value = value;

    struct BothNode *traversal = head->first;
    int insertFlag = 0;

    if (head->nodeNums == 0){
        head->first = traversal;
        head->last = traversal;
    }
    while (traversal){
        if (traversal->value > newNode->value){
            newNode->next = traversal;
            if (traversal == head->first){
                head->first->prev = newNode;
                head->first = newNode;
            }
            else{
                newNode->prev = traversal->prev;
                newNode->prev->next = newNode;
                traversal->prev = newNode;
            }
            insertFlag = 1;
            break;
        }
        traversal = traversal->next;
    }

    if (insertFlag == 0){
        head->last->next = newNode;
        newNode->prev = head->last;
        head->last = newNode;
    }

    head->nodeNums++;
    return head;
}

/*
    delNode: 删除结点
        @head: 链表头指针
        @value: 删除的结点值
        @retval: 链表头结点
*/
struct BothHead *delNode(struct BothHead *head, ElemType value){
    struct BothNode *traversal = head->first;
    
    while (traversal){
        if (traversal->value == value){
            // Step 1: 删除目标是头结点
            if (traversal == head->first){
                head->first = head->first->next;
                // Step 1.1: 头结点, 但只存在一个结点
                if(head->nodeNums == 1)
                    head->last = NULL;
                // Step 1.2: 头结点, 存在多个结点
                else{
                    traversal->next->prev = NULL;
                    traversal->next = NULL;
                }
                free(traversal);
                traversal = head->first;
            }
            // Step 2: 删除目标是尾结点
            else if (traversal == head->last){
                head->last = traversal->prev;
                head->last->next = NULL;
                traversal->prev = NULL;
                free(traversal);
                traversal = NULL;
            }
            // Step 3: 删除结点是中间结点
            else {
                struct BothNode *temp = traversal->next;
                traversal->prev->next = traversal->next;
                traversal->next->prev = traversal->prev;
                traversal->next = NULL;
                traversal->prev = NULL;
                free(traversal);
                traversal = temp;
            }
            head->nodeNums--;
        }
        else{
            traversal = traversal->next;
        }
        
    }

    return head;
}

/*
    selectSortToList: 为双向链表进行选择排序
        @head: 链表头指针
        @retval: 链表头指针
*/
struct BothHead *selectSortToList(struct BothHead *head){
    struct BothNode *i = NULL;
    // 待排序结点值: 98, 34, 78, 56, 23, 99, 39, 12, 45, 76
    // i的范围: 98, 34, 78, 56, 23, 99, 39, 12, 45
    for (i = head->first; i != head->last; i = i->next){
        int min = i->value;
        struct BothNode *minIndex = i;
        struct BothNode *j = NULL;
        // j的范围: 34, 78, 56, 23, 99, 39, 12, 45, 76
        for (j = i->next; j; j = j->next){
            if (min > j->value){
                min = j->value;
                minIndex = j;
            }
        }
        // 找到比i的值更小的结点
        if (minIndex != i){
            int firstFlag = 0;
            int lastFlag = 0;
            if (i == head->first)
                firstFlag = 1;
            if (minIndex == head->last)
                lastFlag = 1;

            // i的前置结点
            struct BothNode *prev = i->prev;
            // i的后置结点
            struct BothNode *next = i->next;
            struct BothNode *iCopy = i;
            // 如果需要交换的两个结点不相邻
            if (iCopy->next != minIndex){
                iCopy->next = minIndex->next; 
                iCopy->prev = minIndex->prev;
                if (minIndex->next)
                    minIndex->next->prev = iCopy;
                minIndex->prev->next = iCopy;
                
                minIndex->next = next; 
                minIndex->prev = prev;
                next->prev = minIndex;
                if (prev)
                    prev->next = minIndex;
            }
            // 如果需要交换的两个结点相邻
            else{
                iCopy->next = minIndex->next;
                iCopy->prev = prev;
                minIndex->next->prev = iCopy;

                minIndex->next = iCopy;
                minIndex->prev = prev;
                prev->next = minIndex;
                
            }

            if (firstFlag) 
                head->first = minIndex;
            if (lastFlag)
                head->last = iCopy;
        }
    }    
    return head;
}

/*
    changeNode: 更改某结点的值为另一个值, 并进行排序
        @head: 链表头指针
        @sourceData: 需要更改的结点的值
        @targetData: 修改后的值
        @retval: 链表头结点
    注意: 修改后的链表一定要重新排序, 否则不一定是有序
*/
struct BothHead *changeNode(struct BothHead *head, ElemType sourceData, ElemType targetData){
    struct BothNode *traversal = head->first;
    while (traversal){
        if (traversal->value == sourceData)
            traversal->value = targetData;

        traversal = traversal->next;
    }
    printf("\n\n更改后:\n");
    printList(head);
    head = selectSortToList(head);
    printf("\n\n排序后:\n");
    printList(head);
    return head;
}


/*
    serchNode: 搜索是否存在该值的结点
        @head: 链表头指针
        @value: 带搜索的结点值
        @reval: 符合的结点个数
*/
int searchNode(struct BothHead *head, ElemType value){
    struct BothNode *traversal = head->first;
    int searchNums = 0;

    while (traversal){
        if (traversal->value == value)
            searchNums++;
        
        traversal = traversal->next;
    }

    return searchNums;
}

/*
    printList: 打印整个链表
        @head: 链表头指针
*/
void printList(struct BothHead *head){
    struct BothNode *traversal = head->first;
    while(traversal){
        printf("Both Way Link List With Head Value = %d\n", traversal->value);
        traversal = traversal->next;
    }
}

/*
    destoryList: 销毁整个链表
        @head: 链表头指针
        @retval: bool类型, 是否销毁掉了链表
*/
bool destoryList(struct BothHead *head){
    struct BothNode *traversal = head->first;
    while (traversal){
        head->first = head->first->next;
        traversal->next = NULL;
        if (head->first)
            head->first->prev = NULL;
        
        free(traversal);
        traversal = head->first;
        head->nodeNums--;
    }
    head->last = NULL;
    
    if (head->first == NULL && head->last == NULL && head->nodeNums == 0){
        free(head);
        return true;
    }
    else
        return false;

}













