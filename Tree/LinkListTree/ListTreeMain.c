#include <stdio.h>
#include <stdlib.h>
#include "ListTree.h"

int main()
{
    TNode *treeHead = NULL;
    int insertArray[9] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    for (int i = 0; i < 9; i++){
        treeHead = insertTreeNode(treeHead, insertArray[i]);
    }
    
    printf("前序遍历为: ");
    preOrder(treeHead);
    putchar('\n');

    printf("中序遍历为: ");
    inOrder(treeHead);
    putchar('\n');

    printf("后序遍历为: ");
    postOrder(treeHead);
    putchar('\n');

    printf("层次遍历为: ");
    levelOrder(treeHead);
    putchar('\n');

    TNode *root = treeHead;
    deleteNode(root, treeHead, 6);

    printf("删除某个节点后:\n");
    printf("前序遍历为: ");
    preOrder(treeHead);
    putchar('\n');

    printf("中序遍历为: ");
    inOrder(treeHead);
    putchar('\n');

    printf("后序遍历为: ");
    postOrder(treeHead);
    putchar('\n');

    printf("层次遍历为: ");
    levelOrder(treeHead);
    putchar('\n');

    printf("root: %d\n", root->value);

    TNode *searchRet = search(root, 7);

    if (searchRet)
        printf("search success!!!, value = %d\n", searchRet->value);
    else
        printf("search failed!!!\n");

    return 0;
}

