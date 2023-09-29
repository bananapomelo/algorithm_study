#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct CirCleLinkListHead{
    struct CirCleLinkListNode *first;
    struct CirCleLinkListNode *last;
    int nodeNums;
}CSHead;

typedef struct CirCleLinkListNode{
    struct CirCleLinkListNode *next;
    ElemType value;
}CSNode;

int loopDetection(CSHead *head);
CSHead *createList();
void printList(CSHead *head);
bool destroyList(CSHead *head);

int main()
{

    /* 
                注意: 打印和销毁的退出条件要换成节点个数
    */
    CSHead * head = createList();
    printf("\n\n初始化后: \n");
    printList(head);
    
    // 前插n个节点, 
    int addNum = 0;
    scanf("%d", &addNum);
    while (addNum--){
        CSNode *newNode = malloc(sizeof(*newNode));
        newNode->value = 1;
        newNode->next = head->first;
        head->first = newNode;
        head->nodeNums++;
        printf("adf\n");
    }
    
    printf("\n\n初始化后: \n");
    printList(head);
    // proveCircle(head); 
    printf("\n\n");   


    // head->last->next = NULL;
    int index = loopDetection(head);
    switch (index){
        case -1: printf("no cycle\n"); break;
        default: printf("tail connects to node index %d\n", index); break;
    }

    head->last->next = head->first; 
    if (destroyList(head))
        printf("destory List Complete ^_^\n");

/*
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

int loopDetection(CSHead *head){

    if (head == NULL || head->first->next == head->first){
        return -1;
    }

    CSNode *fast = head->first;
    CSNode *slow = head->first;

    // Strp1: 如果指针指向空就一定不是环路
    while (fast && slow){
        // Step1.1: 快指针走两步
        fast = fast->next;
        if (fast)
            fast = fast->next;

        // Step1.2: 慢指针走一步
        slow = slow->next;

        // Step2: 第一次相遇
        if (fast == slow){
            fast = head->first;
            int index = 0;

            // Step3: 快指针从头开始, 慢指针从第一次相遇位置开始, 步长为1, 等待第二次相遇
            while (fast != slow){
                fast = fast->next;
                slow = slow->next;
                index++;
            }
            return index;
        }
    }
    
    return -1;
}


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
    printList: 打印整个链表
        @head: 链表头指针
*/
void printList(CSHead *head){
    CSNode *traversal = head->first;
    int printNum = head->nodeNums;
    while (printNum--){
        printf("Circle Link List With Head Value: %d\n", traversal->value);
        traversal = traversal->next;
    }
}

/*
    destroyList: 销毁链表
        @head: 链表头指针
        @retval: 返回是否销毁成功
*/
bool destroyList(CSHead *head){

    CSNode *traversal = head->first;
    while (head->nodeNums){
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
