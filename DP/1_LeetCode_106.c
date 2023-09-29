int post_idx;

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} hashTable;

hashTable* idx_map;

void insertHashTable(int x, int y) {
    hashTable* rec = malloc(sizeof(hashTable));
    rec->key = x;
    rec->val = y;
    HASH_ADD_INT(idx_map, key, rec);
}

int queryHashTable(int x) {
    hashTable* rec;
    HASH_FIND_INT(idx_map, &x, rec);
    return rec->val;
}

struct TreeNode* helper(int in_left, int in_right, int* inorder, int* postorder) {
    // 如果这里没有节点构造二叉树了，就结束
    if (in_left > in_right) {
        return NULL;
    }

    // 选择 post_idx 位置的元素作为当前子树根节点
    int root_val = postorder[post_idx];
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = root_val;

    // 根据 root 所在位置分成左右两棵子树
    int index = queryHashTable(root_val);

    // 下标减一
    post_idx--;
    // 构造右子树
    root->right = helper(index + 1, in_right, inorder, postorder);
    // 构造左子树
    root->left = helper(in_left, index - 1, inorder, postorder);
    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    // 从后序遍历的最后一个元素开始
    post_idx = postorderSize - 1;

    // 建立（元素，下标）键值对的哈希表
    idx_map = NULL;
    int idx = 0;
    for (int i = 0; i < inorderSize; i++) {
        insertHashTable(inorder[i], idx++);
    }

    return helper(0, inorderSize - 1, inorder, postorder);
}
