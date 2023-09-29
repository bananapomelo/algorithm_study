#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"
#include "LinkQueue.h"

/*
    newTreeRoot: 创建根节点
        @retval: 返回根节点指针
*/
ATRoot *newTreeRoot() {
    ATRoot *node = (ATRoot *)malloc(sizeof(*node));
    node->root = NULL;

    return node;
}

/*
    newTreeNode: 新建节点
        @value: 节点
        @retval: 返回节点指针
*/
ATNode *newTreeNode(ElemType value) {
    ATNode *newNode = (ATNode *)malloc(sizeof(*newNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    newNode->value = value;

    return newNode;
}

/*
    getHeight: 获取节点高度(该节点到最远节点走过的边数)
        @node: 待获取高度的节点
        @retval: 节点高度
*/
int getHeight(ATNode *node) {
    // 空节点的高度为-1
    if (node == NULL)
        return -1;

    return node->height;
}

/*
    updataHeight: 更新节点高度
        @node: 待更新高度的节点
        @retval: 空
*/
void updataHeight(ATNode *node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    // 因node和node->left有一条边相连, 所以需要加1
    if (leftHeight > rightHeight)
        node->height = leftHeight + 1;
    else
        node->height = rightHeight + 1;

    return ;
}

/*
    blanceFactor: 获取节点的平衡因子(左右节点高度差)
        @node: 待获取平衡因子的节点
        @retval: 平衡因子
*/
int blanceFactor(ATNode *node) {
    // 空节点的平衡因子为0
    if (node == NULL)
        return 0;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return leftHeight - rightHeight;
}

/*
    leftRotate: 左旋
        @node: 失衡节点
        @retval: 恢复平衡后, 返回节点
*/
ATNode *leftRotate(ATNode *node) {
    ATNode *child = node->right;
    ATNode *grandChild = child->left;

    child->left = node;
    node->right = grandChild;

    updataHeight(node);
    updataHeight(child);

    return child;
}

/*
    rightRotate: 右旋
        @node: 失衡节点
        @retval: 恢复平衡后, 返回节点
*/
ATNode *rightRotate(ATNode *node) {
    ATNode *child = node->left;
    ATNode *grandChild = child->right;

    child->right = node;
    node->left = grandChild;

    updataHeight(node);
    updataHeight(child);

    return child;
}

/*
    rotate: 旋转操作(根据平衡因子判断用哪种旋转)
        @node: 失衡节点
        @retval: 恢复平衡后的节点
*/
ATNode *rotate(ATNode *node) {
    int blance = blanceFactor(node);

    if (blance > 1) {
        if (blanceFactor(node->left) >= 0) {
            return rightRotate(node);
        } else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else if (blance < -1) {
        if (blanceFactor(node->right) <= 0) {
            return leftRotate(node);
        } else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

/*
    insertNode: 插入节点
        @node: 根节点指针
        @value: 待插入值
        @retval: 空
*/
void insertNode(ATRoot *node, ElemType value) {
    node->root = insertHelper(node->root, value);
}

/*
    insertHelper: 插入函数(递归寻找位置)
        @node: 根节点
        @value: 待插入值
        @retval: 返回根节点
*/
ATNode *insertHelper(ATNode *node, ElemType value) {
    if (node == NULL) {
        return newTreeNode(value);
    }

    if (node->value > value) {
        node->left = insertHelper(node->left, value);
    } else if (node->value < value) {
        node->right = insertHelper(node->right, value);
    } else {
        return node;
    }

    // 自底向上更新节点高度
    updataHeight(node);

    // 自底向上平衡节点
    node = rotate(node);

    return node;
}

/*
    removeNode: 删除节点
        @node: 根节点指针
        @value: 待删除节点值
        @retval: 空
*/
void removeNode(ATRoot *node, ElemType value) {
    node->root = removeHelper(node, node->root, value);
}

/*
    removeHelper: 删除函数
        @root: 根节点指针, 用于寻找父节点, 删除节点用
        @node: 根节点, 用于递归
        @value: 待删除节点值
        @retval: 删除后的根节点
*/
ATNode *removeHelper(ATRoot *root, ATNode *node, ElemType value) {
    ATNode *child;
    if (node == NULL) {
        return NULL;
    }

    // 节点值大于待删除值
    if (node->value > value) {
        node->left = removeHelper(root, node->left, value);
    // 节点值小于待删除值
    } else if (node->value < value) {
        node->right = removeHelper(root, node->right, value);
    // 找到了待删除的节点
    } else {
        // 只有一个子节点
        if (node->left == NULL || node->right == NULL) {
            child = node->left;
            if (node->right != NULL) {
                child = node->right;
            }

            if (child == NULL) {
                return delConnect(root->root, node, child);
            } else {
                node = delConnect(root->root, node, child);
            }
        } else { // 两个节点都存在, 寻找到左子树中最大的值, 与node交换值, 删除左子树中最大的节点
            ATNode *delNode = node->left;

            // 找到左子树中最大值
            while (delNode->right) {
                delNode = delNode->right;
            }
            
            int tempVal = delNode->value;
            node->left = removeHelper(root, node->left, delNode->value);
            node->value = tempVal;
        }
    }

    // 自底向上更新节点高度
    updataHeight(node);

    // 自底向上平衡节点
    node = rotate(node);

    return node;
}

/*
    delConnect: 释放节点内存
        @root: 根节点
        @node: 待删除节点
        @connectNode: 待删除节点的子节点
        @retval: 返回释放后的节点
*/
ATNode *delConnect(ATNode *root, ATNode *node, ATNode *connectNode) {
    // 没有子节点, 直接释放node
    if (connectNode == NULL) {
        node->left = NULL; node->right = NULL; 
        free(node); node = NULL;
        return node;
    }

    ATNode *current = root;
    ATNode *currFather = NULL;

    // 寻找待删除节点和其父结点, 父结点用于连接
    while (current != node) {
        currFather = current;
        if (current->value > node->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // 判断node在父结点的哪一边, 并断连
    if (currFather->right == node) {
        currFather->right = connectNode;
    } else {
        currFather->left = connectNode;
    }

    node->left = NULL; node->right = NULL;
    free(node); node = NULL;

    return connectNode;
}

/*
    search: 递归搜索节点
        @root: 根节点
        @target: 带搜索节点值
        @retval: 找到返回节点, 否则返回空
*/
ATNode *search(ATNode *root, ElemType target) {
    if (root == NULL || root->value == target) {
        return root;
    }

    if (root->value > target)
        search(root->left, target);
    else
        search(root->right, target);

}

/*
    inOrder: 前序遍历(根左右)
        @current: 根节点
        @retval: 空
*/
void inOrder(ATNode *current) {
    if (current == NULL){
        return ;
    }
    
    inOrder(current->left);

    printf("%d ", current->value);

    inOrder(current->right);
}

/*
    postOrder: 中序遍历(从小到大)
        @current: 根节点
        @retval: 空
*/
void postOrder(ATNode *current) {
    if (current == NULL){
        return ;
    }

    postOrder(current->left);
    postOrder(current->right);
    printf("%d ", current->value);
}

/*
    levelOrder: 层次遍历(广搜)
        @rootNode: 根节点
        @retval: 空
*/
void levelOrder(ATNode *rootNode) {
    LQueue *temp = createLinkQueue();

    push(temp, rootNode);

    while (!isEmpty(temp)) {
        ATNode *popNode = pop(temp);
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





