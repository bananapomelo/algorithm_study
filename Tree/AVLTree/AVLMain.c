#include <stdio.h>
#include "AVLTree.h"

int main() {
    ATRoot *tree = newTreeRoot();

    if (tree->root == NULL)
        printf("NULL\n");

    insertNode(tree, 2);
    insertNode(tree, 1);
    insertNode(tree, 3);
    insertNode(tree, 5);
    insertNode(tree, 4);

    printf("tree: %d\n", tree->root->value);

    printf("前序遍历\n");
    inOrder(tree->root);
    putchar('\n');

    printf("中序遍历\n");
    postOrder(tree->root);
    putchar('\n');

    printf("层次遍历\n");
    levelOrder(tree->root);
    putchar('\n');

    removeNode(tree, 3);
    printf("\n删除后:\n");

    ATNode *searchRet = search(tree->root, 3);

    if (searchRet)
        printf("search success!!!, value = %d\n", searchRet->value);
    else
        printf("search failed!!!\n");

    printf("前序遍历\n");
    inOrder(tree->root);
    putchar('\n');

    printf("中序遍历\n");
    postOrder(tree->root);
    putchar('\n');

    printf("层次遍历\n");
    levelOrder(tree->root);
    putchar('\n');

    return 0;
}




