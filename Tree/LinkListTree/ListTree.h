#ifndef __LISTTREE_H__
#define __LISTTREE_H__

typedef int ElemType;

typedef struct TreeNode {
    // int nodeHeight;
    ElemType value;
    struct TreeNode *left;
    struct TreeNode *right;
}TNode;

extern TNode *insertTreeNode(TNode *rootNode, ElemType value);
extern void preOrder(TNode *current);
extern void inOrder(TNode *current);
extern void postOrder(TNode *current);
extern void levelOrder(TNode *rootNode);
extern int deleteNode(TNode *root, TNode *node, int delValue);
extern TNode *findFatherNode(TNode *root, TNode *node, int delValue);
extern TNode *search(TNode *root, ElemType target);

#endif