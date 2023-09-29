#include <iostream>
using namespace std;

// Eg1:给定一个二叉树，搜索并记录所有值为的节点，请返回节点列表。
void preOrder(TreeNode* root) {
    if (root == nullptr) {
        return ;
    }
    if (root->val == 7) {
        res.push_back(root);
    }
    preOrder(root->left);
    preOrder(root->right);
}

// Eg2:在二叉树中搜索所有值为 的节点，请返回根节点到这些节点的路径。
void preOrder(TreeNode* root) {
    if (root == nullptr) {
        return ;
    }

    // 尝试
    path.push_back(root);
    if (root->val == 7) {
        // 记录解
        res.push_back(path);
    }
    preOrder(root->left);
    preOrder(root->right);
    // 回退
    path.pop_back(root);
}

// Eg3:在二叉树中搜索所有值为的节点，请返回根节点到这些节点的路径，
// 并要求路径中不包含值为3的节点。
void preOrder(TreeNode* root) {
    // 剪枝
    if (root = nullptr || root->val == 3) {
        return ;
    }

    // 尝试
    path.push_back(root);
    if (root->val == 7) {
        // 记录解
        res.push_back(path);
    }
    preOrder(root->left);
    preOrder(root->right);
    // 回退
    path.pop_back();
}

// 回溯算法框架
void backtrack(State *state, vector<Choice *> &choices, vector<State *> &res) {
    // 判断是否是解
    if (isSolution(state)) {
        // 记录解
        recordSolution(state, res);
        // 停止继续搜索
        return ;
    }
    // 遍历所有选择
    for (Choice choice : choices) {
        // 剪枝: 判断选择是否合法
        if (isValid(state, choice)) {
            // 尝试：做出选择，更新状态
            makeChoice(state, choice);
            backtrack(state, choices, res);
            // 回退：撤销选择，恢复到之前的状态
            undoChoice(state, choice);
        }
    }
}

/* 判断当前状态是否是解 */
bool isSolution(vector<TreeNode *> &state) {
    return !state.empty() && state.back()->val == 7;
}

/* 记录解 */
void recordSolution(vector<TreeNode *> &state, vector<vector<TreeNode *>> &res) {
    res.push_back(state);
}

/* 判断在当前状态下，该选择是否合法 */
bool isValid(vector<TreeNode *> &state, TreeNode *choice) {
    return choice != nullptr && choice->val != 3;
}

/* 更新状态 */
void makeChoice(vector<TreeNode *> &state, TreeNode *choice) {
    state.push_back(choice);
}

/* 恢复状态 */
void undoChoice(vector<TreeNode *> &state, TreeNode *choice) {
    state.pop_back();
}

// 回溯算法：Eg3
void backtrack(vector<TreeNode *> &state, vector<TreeNode *> &choices, vector<vecotr<TreeNode *>> &res) {
    // 检查是否为解
    if (isSolution(state)) {
        // 记录解
        recordSolution(state, res);
    }
    // 遍历所有选择
    for (TreeNode *choice : choices) {
        // 剪枝：检查选择是否合法
        if (isValid(state, choice)) {
            // 尝试：做出选择，更新状态
            makeChoice(state, choice);
            // 进行下一轮选择
            vector<TreeNode *> nextChoices{choice->left, choice->right};
            backtrack(state, nextChoices, res);
            // 回退：撤销选择，恢复到之前的状态
            undoChoice(state, choice);
        }
    }
}


