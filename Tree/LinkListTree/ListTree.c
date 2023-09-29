#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ListTree.h"
#include "LinkQueue.h"

/*
    insertTreeNode: 
        @rootNode: 
        @value: 
        @retval: 
*/
TNode *insertTreeNode(TNode *rootNode, ElemType value) {
    TNode *newNode = (TNode *)malloc(sizeof(*newNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (rootNode == NULL) {
        rootNode = newNode;
        return rootNode;
    }

    TNode *traversal = rootNode;
    while (traversal) {
        // 插入值比该节点小, 且左子节点为空, 插入左子节点
        if (newNode->value < traversal->value) {
            if (traversal->left == NULL) {
                traversal->left = newNode;
                break;
            }
            traversal = traversal->left;
        }
        // 插入值比该节点大, 且右子节点为空, 插入右子节点
        else if (newNode->value > traversal->value) {
            if (traversal->right == NULL) {
                traversal->right = newNode;
                break;
            }
            traversal = traversal->right;
        }
        else {
            printf("不允许出现重复的数\n");
            break;
        }
    }

    return rootNode;
}

/*
    preOrder: 
        @current: 
        @retval: 
*/
void preOrder(TNode *current) {
    if (current == NULL){
        return ;
    }
    
    printf("%d ", current->value);

    preOrder(current->left);
    preOrder(current->right);
}

/*
    inOrder: 
        @current: 
        @retval: 
*/
void inOrder(TNode *current) {
    if (current == NULL){
        return ;
    }
    
    inOrder(current->left);

    printf("%d ", current->value);

    inOrder(current->right);
}

/*
    postOrder: 
        @current: 
        @retval: 
*/
void postOrder(TNode *current) {
    if (current == NULL){
        return ;
    }

    postOrder(current->left);
    postOrder(current->right);
    printf("%d ", current->value);
}

/*
    levelOrder: 
        @rootNode: 
        @retval: 
*/
void levelOrder(TNode *rootNode) {
    LQueue *temp = createLinkQueue();

    push(temp, rootNode);

    while (!isEmpty(temp)) {
        TNode *popNode = pop(temp);
        printf("%d ", popNode->value);

        if (popNode->left) {
            push(temp, popNode->left);
        }
        if (popNode->right) {
            push(temp, popNode->right);
        }
        
        // free(popNode);
        popNode = NULL;
    }

    putchar('\n');
    destructLinkQueue(temp);

    return ;
}

/*
    deleteNode: 
        @root: 
        @node: 
        @delValue: 
        @retval: 
*/
/*
    删除情况:
        1. 要删除的节点(delNode)没有左节点: 找到 delNode 的父结点, 指向右节点
        2. 要删除的节点(delNode)没有右节点: 找到 delNode 的父结点, 指向左节点
        3. 要删除的节点(delNode)左右节点都有: 从 delNode 左子树开始, 寻找最大的节点(maxNode), 
                                交换 delNode 和 maxNode 值, 删除maxNode
            注意: 如果 delNode->left == maxNode   则delNode->left = maxNode->left
                    (讲解) 左子树的度为1或0 且没有右节点, 则delNode->left = maxNode->left;
                如果 delNode->left != maxNode   则delNode->right = maxNode->left
                    (讲解) 当 maxNode->left != NULL 时, 需要连接一下, 防止 maxNode->left 为野指针 
        4. 没找到就递归, 如果key(待删除)的值比该节点小, 向左递归, 反之向右
*/

int deleteNode(TNode *root, TNode *node, int delValue) {
    if (node == NULL)
        return -1;
    else{
        if (node->value == delValue) {
            // 当我执行删除操作 需要先定位到node的父结点
            TNode *fatherNode = findFatherNode(root, node, delValue);
            TNode *delNode = NULL;

            if (node->left == NULL) {
                delNode = node;
                node = node->right;

                /*为了判断 待删除结点是前一个结点的左边还是右边*/
                if (fatherNode->left == delNode)
                    fatherNode->left = node;
                else
                    fatherNode->left = node;

                free(delNode);
                delNode = NULL;
            }
            else if (node->right == NULL) {
                delNode = node;
                node = node->left;

                if (fatherNode->left == delNode)
                    fatherNode->left = node;
                else
                    fatherNode->right = node;
                
                free(delNode);
                delNode = NULL;
            }
            // 左右子树都不为空
            else {
                // 记录左子树最大值的父结点
                TNode *delFather = node;
                delNode = node->left;

                while (delNode->right) {
                    delFather = delNode;
                    delNode = delNode->right;
                }

                node->value = delNode->value;

                if (delNode == node->left){
                    delFather->left = delNode->left;
                    free(delNode);
                    delNode = NULL;
                }
                else{
                    delFather->right = delNode->left;
                    free(delNode);
                    delNode = NULL;
                }
               
            }
        }
        else {
            if (delValue < node->value)
                deleteNode(root, node->left, delValue);
            else
                deleteNode(root, node->right, delValue);
        }
    }
}


/*
    findFatherNode: 
        @root: 
        @node: 
        @delValue: 
        @retval: 
*/
TNode *findFatherNode(TNode *root, TNode *node, int delValue) {
    if (root == NULL || root == node) {
        return node;
    }
    else {
        if (root->left->value == delValue) {
            return root;
        }
        else if (root->right->value == delValue) {
            return root;
        }
        else{
            if (delValue < root->value){
                findFatherNode(root->left, node, delValue);
            }
            else{
                findFatherNode(root->right, node, delValue);
            }
        }
    }

}

/*
    search: 搜索节点
        @root: 当前搜索的节点
        @target: 目标节点值
        @retval: 找到返回节点, 没找到返回NULL
*/
TNode *search(TNode *root, ElemType target) {
    if (root == NULL || root->value == target) {
        return root;
    }

    if (root->value > target)
        search(root->left, target);
    else
        search(root->right, target);

}



















