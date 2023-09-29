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

bool judgeSubList(SHead *listA, SHead *listB);
SHead *createHead (void);
void printList (SHead *head);
bool destroyList (SHead *head);

int main()
{
    SHead *ListA = createHead();
    SHead *ListB = createHead();

    printf("\n\n链表A:\n");
    printList(ListA);

    printf("\n\n链表B:\n");
    printList(ListB);

    if (judgeSubList(ListA, ListB)){
        printf("\n\nB是A的子链表^_^\n");
    }
    else{
        printf("\n\nB不是A的子链表~_~\n");
    }

    if (destroyList(ListA))
        printf("\n\nList A Destroy success ^_^\n");
    if (destroyList(ListB))
        printf("\n\nList B Destroy success ^_^\n");
/* 终端输入以初始化两个链表
4
2
3
3
3
4
6
5
0
3
3
4
0

*/
    return 0;
}


/*
    commonOfLists: 判断listB是不是ListA的子链表
        @listA: 链表A的头指针
        @listB: 链表B的头指针
        @retval: 1(listB是listA子链表),, 0(不是子链表)
*/
bool judgeSubList(SHead *listA, SHead *listB){
    if (listA->nodeNums < listB->nodeNums){
        return false;
    }

    int remainNode = listA->nodeNums;
    // 遍历A链表
    SNode *startNodeA = listA->first;

    // listA剩余的节点数量比B的数量多
    while (remainNode >= listB->nodeNums){
        if (startNodeA->value == listB->first->value){
            SNode *ifSubListA = startNodeA;
            SNode *ifSubListB = listB->first;
            
            for (int i = 0; i < listB->nodeNums; i++){
                if (ifSubListA->value == ifSubListB->value){
                    ifSubListA = ifSubListA->next;
                    ifSubListB = ifSubListB->next;
                }
                else{
                    break;
                }
            }

            if (ifSubListB == NULL){
                return true;
            }
        }

        startNodeA = startNodeA->next;
        remainNode--;
    }

    return false;
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






