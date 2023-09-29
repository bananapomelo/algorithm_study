#ifndef __AVLTREE_H__
#define __AVLTREE_H__


typedef int ElemType;

typedef struct AVLTreeRoot {
    struct AVLTreeNode *root;
}ATRoot;

typedef struct AVLTreeNode {
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
    ElemType value;
    int height;
}ATNode;

extern ATRoot *newTreeRoot();
extern ATNode *newTreeNode(ElemType value);
extern int getHeight(ATNode *node);
extern void updataHeight(ATNode *node);
extern int blanceFactor(ATNode *node);
extern ATNode *leftRotate(ATNode *node);
extern ATNode *rightRotate(ATNode *node);
extern ATNode *rotate(ATNode *node);
extern void insertNode(ATRoot *node, ElemType value);
extern ATNode *insertHelper(ATNode *node, ElemType value);
extern void removeNode(ATRoot *node, ElemType value);
extern ATNode *removeHelper(ATRoot *root, ATNode *node, ElemType value);
extern ATNode *delConnect(ATNode *root, ATNode *node, ATNode *connectNode);
extern void inOrder(ATNode *current);
extern void postOrder(ATNode *current);
extern void levelOrder(ATNode *rootNode);
extern ATNode *search(ATNode *root, ElemType target);

#endif