#include <stdio.h>
#include "SingleLinkList.h"

int main()
{
    // 1 1 1 2 3 4 5 6 7 8 9 10 
    struct ListHead *head = createList ();
    printf("\nNo: \n");
    printNode(head);

    // ��
    head = addNode (head, 99);
    printf("\nadd: \n");
    printNode(head);

    // ɾ
    head = delNode (head, 2);
    printf("\ndel: \n");
    printNode(head);

    // ��
    head = changeNode (head, 1, 66);
    printf("\nchange: \n");
    printNode(head);

    // ��
    ElemType target = 66;
    ElemType count = findNode (head, target);
    printf("\nfind:\n%d nums = %d\n", target, count);
    destoryList(head);

    return 0;
}